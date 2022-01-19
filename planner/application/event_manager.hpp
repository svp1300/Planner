#ifndef EVENT_MANAGER_HPP
#define EVENT_MANAGER_HPP

#include <vector>

#include "../model/calendar_query.hpp"
#include "../model/calendar_event.hpp"

enum ModificationResult {kInvalid, kOverlap, kFailure, kSuccess};

class EventManager {
    protected:
        // For the time values in the query:
        // If the time conditions are present, a condition for
        // returning true is that the event time overlaps with the time
        // in the query.
        // For name and category in the query: 
        // If the value is in the query, then a condition for returning 
        // true is that the value string is contained within the corresponding 
        // attribute in the event.
        // If and only if all of the included conditions are true, then the
        // function returns true.
        bool CheckQueryConditions(EventQuery query, CalendarEvent event);

        // Find and return all events where the query conditions are true.
        virtual std::vector<CalendarEvent> QueryEvents(EventQuery query);

        // Attempt to insert an event while enforcing ACID principles.
        // Returns the result of the operation.
        virtual ModificationResult InsertEvent(CalendarEvent event);

        // Attempt to delete an event while enforcing ACID principles.
        // Returns the result of the operation.
        virtual ModificationResult DeleteEvent(CalendarEvent event);
    public:
        // Subclasses open database connections, file handles,
        // and anything needed before running queries.
        virtual void Initialize();

        // Close any database connections or file handles used.
        virtual void Close();
};

#endif