#include "../aurora.h"
#include "event.h"
#include "event_manager.h"

namespace aurora {

EventManager::EventManager() : active_queue_index(0) {

}

EventManager::~EventManager() {
  
}

int EventManager::AddEvent(const char* event_name) {
  Event e(event_name);

  if (GetEvent(event_name)!=NULL)
    return -1;

  events_.push_back(e);
  events_map.insert(EventListenerMapEntry(e.hash(),EventListenerList()));
  return 0;
}

int EventManager::AddEventListener(const char* event_name, EventListener del) {
  
  Event* e = GetEvent(event_name);
  if (e == NULL)
    return -1;

  EventListenerList& list = events_map[e->hash()];
  list.push_back(del);
  return 0;

}

int EventManager::RemoveAllEvents() {
  
  events_.clear();
  events_map.clear();
  return 0;
}

int EventManager::QueueEvent(const char* event_name, EventData data) {
  
  if (GetEvent(event_name) == NULL)
    return -1;
  
  Event e(event_name);
  data.time_stamp = engine()->total_cycles();
  EventQueueEntry item(e.hash(),data);
  active_queue().push(item);

  return 0;
}

Event* EventManager::GetEvent(const char* event_name) {
  EventList::iterator i;
  Event e(event_name);
  for(i=events_.begin(); i != events_.end(); ++i) {
    if ( (*i) == e)
      return &(*i);
  }

  return NULL;
}

int EventManager::Process(uint64_t dt) {

  while(active_queue().size() > 0) {
    EventQueueEntry entry = active_queue().front();
    active_queue().pop();

    //execute listeners
    {
      EventListenerList& list = events_map[entry.first];
      for ( EventListenerList::iterator i = list.begin(); i != list.end(); ++i) {
        int result = (*i)(entry.first,entry.second);
        if (result != 0) //stop propogation
          break;
      }
    }
    //if time exceeded, exit
  }

  //if queue empty
  active_queue_index = (active_queue_index+1) % EventManager::queue_array_size;

  return 0;
}

}



