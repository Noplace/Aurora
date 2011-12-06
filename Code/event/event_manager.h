#ifndef EVENT_MANAGER_H
#define EVENT_MANAGER_H

#include <stdint.h>
#include <vector>
#include <queue>
#include <map>
#include "../engine_component.h"


namespace aurora {

class Event;
typedef int (*EventListener)(EventHash,EventData EventData);
typedef std::vector<Event> EventList;
typedef std::vector<EventListener> EventListenerList;
typedef std::map<EventHash,EventListenerList> EventListenerMap;
typedef std::pair<EventHash, EventListenerList> EventListenerMapEntry;
typedef std::pair<EventHash, EventData> EventQueueEntry;


class EventManager : public EngineComponent {
 public:
  EventManager();
  ~EventManager();
  int AddEvent(const char* event_name);
  int AddEventListener(const char* event_name, EventListener listner);
  int RemoveAllEvents();
  int QueueEvent(const char* event_name, EventData data);
  Event* GetEvent(const char* event_name);

  int Process(uint64_t dt);
 private:
  static const int queue_array_size = 2;
  std::queue<EventQueueEntry>& active_queue() {
    return event_queues_[active_queue_index];
  }
  int active_queue_index;
  std::queue<EventQueueEntry> event_queues_[queue_array_size];
  EventList events_;
  EventListenerMap events_map;
};

}

#endif