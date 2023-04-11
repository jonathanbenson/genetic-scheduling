
#include <algorithm>
#include <map>
#include <set>
#include "GA.h"


FacilitatorLoadInfo GetFacilitatorLoadInfo(const Schedule& s, int facilitator_id)
{
    // Computes information concerning the load on the facilitator with regards
    // to overseeing events.

    // Initialize the output struct
    FacilitatorLoadInfo info;
    info.Total = 0;
    info.NumNonConflicts = 0;
    info.NumConflicts = 0;
    info.NumConsecutive = 0;

    // Find all assigned events for the facilitator
    std::vector<Event> assignedEvents;
    for (Event e : s.events)
    {
        if (e.FacilitatorIndex == facilitator_id)
        {
            assignedEvents.push_back(e);
        }
    }
    // Record the total number of assigned events
    info.Total = assignedEvents.size();

    // Compute the number of conflicts and the number of consecutive slots
    for (Event e : assignedEvents)
    {
        for (Event f : s.events)
        {
            if (e.ActivityIndex != f.ActivityIndex)
            {
                if (e.TimeIndex == f.TimeIndex)
                {
                    // If two events have the same time index but different activity indices,
                    // they conflict with each other.
                    info.NumConflicts++;
                }
                else if (e.TimeIndex - f.TimeIndex == 1)
                {
                    // If two events have adjacent time indices and different activity indices,
                    // they are consecutive events for the same activity.
                    for (Event g : assignedEvents)
                    {
                        if (g.ActivityIndex == e.ActivityIndex && g.TimeIndex == f.TimeIndex)
                        {
                            info.NumConsecutive++;
                            break;
                        }
                    }
                }
            }
        }
    }

    // Compute the number of assigned events that do not have conflicts
    std::set<int> uniqueActivities;
    for (Event e : assignedEvents)
    {
        bool hasConflict = false;
        for (Event f : s.events)
        {
            if (e.ActivityIndex != f.ActivityIndex && e.TimeIndex == f.TimeIndex)
            {
                hasConflict = true;
                break;
            }
        }
        if (!hasConflict) {
            uniqueActivities.insert(e.ActivityIndex);
        }
    }

    info.NumNonConflicts = uniqueActivities.size();

    // Return the output struct
    return info;
}




double Fitness(const Schedule& s, const std::vector<Activity>& activities, const std::vector<Room>& rooms, const std::vector<double>& times, const std::vector<std::string>& facilitators)
{
    double fitness = 0;

    for (Event e : s.events)
    {
        const Activity& activity = activities.at(e.ActivityIndex);
        const Room& room = rooms.at(e.RoomIndex);

        // penalize if event is scheduled at the same time in the same room as another one of the events
        for (Event f : s.events)
            if ((e.ActivityIndex != f.ActivityIndex) && (e.RoomIndex == f.RoomIndex) && (e.TimeIndex == f.TimeIndex))
                fitness -= .5;

        /*
        Room size:
            Activity is in a room too small for its expected enrollment: -0.5
            Activity is in a room with capacity > 3 times expected enrollment: -0.2
            Activity is in a room with capacity > 6 times expected enrollment: -0.4
            Otherwise + 0.3
        */
        if (room.Capacity * 6 > activity.ExpectedEnrollment)
            fitness -= .4;
        else if (room.Capacity * 3 > activity.ExpectedEnrollment)
            fitness -= .2;
        else if (room.Capacity < activity.ExpectedEnrollment)
            fitness -= .5;
        else
            fitness += .3;

        // Activity is overseen by a preferred facilitator: + 0.5
        if (std::find(activity.PreferredFacilitators.begin(), activity.PreferredFacilitators.end(), facilitators.at(e.FacilitatorIndex)) != facilitators.end())
            fitness += .5;     
        // Activity is overseen by another facilitator listed for that activity: +0.2
        else if (std::find(activity.OtherFacilitators.begin(), activity.OtherFacilitators.end(), facilitators.at(e.FacilitatorIndex)) != facilitators.end())
            fitness += .2;
        // Activity is overseen by some other facilitator: -0.1
        else
            fitness -= .1;

    }

    /*
    Facilitator load:
        Activity facilitator is scheduled for only 1 activity in this time slot: + 0.2
        Activity facilitator is scheduled for more than one activity at the same time: - 0.2
        Facilitator is scheduled to oversee more than 4 activities total: -0.5
        If any facilitator scheduled for consecutive time slots: + .25
    */
    for (int facilitatorIndex = 0; facilitatorIndex < facilitators.size(); facilitatorIndex++)
    {
        FacilitatorLoadInfo info = GetFacilitatorLoadInfo(s, facilitatorIndex);

        fitness += (info.NumNonConflicts * .2);
        fitness -= (info.NumConflicts * .2);

        if (info.Total > 4)
            fitness -= .5;

        fitness += (info.NumConsecutive * .25);
        
    }

}

Schedule TournamentSelect(const std::vector<Schedule>& population, int n)
{

}

Schedule Crossover(const Schedule& p, const Schedule& q)
{

}

void Mutate(double mutationRate)
{

}