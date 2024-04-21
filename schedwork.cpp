#include "schedwork.h"
#include <iostream>
#include <vector>
#include <functional>

using namespace std;

static const Worker_T INVALID_ID = (unsigned int)-1;

bool assignWorkers(size_t day, const AvailabilityMatrix& avail, size_t dailyNeed, size_t maxShifts, DailySchedule& sched, vector<size_t>& shifts);

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
) {
    if(avail.empty() || dailyNeed == 0 || maxShifts == 0) {
        return false;
    }
    sched.clear();
    sched.resize(avail.size(), vector<Worker_T>(dailyNeed, INVALID_ID));
    vector<size_t> shifts(avail[0].size(), 0);

    return assignWorkers(0, avail, dailyNeed, maxShifts, sched, shifts);
}

bool assignWorkers(size_t day, const AvailabilityMatrix& avail, size_t dailyNeed, size_t maxShifts, DailySchedule& sched, vector<size_t>& shifts) {
    if (day == avail.size()) {
        return true;
    }

    function<bool(size_t, size_t)> tryAssign = [&](size_t workerIndex, size_t assignedCount) -> bool {
        if (assignedCount == dailyNeed) {
            return assignWorkers(day + 1, avail, dailyNeed, maxShifts, sched, shifts);
        }
        if (workerIndex == avail[day].size()) {
            return false;
        }

        if (avail[day][workerIndex] && shifts[workerIndex] < maxShifts) {
            sched[day][assignedCount] = workerIndex;
            shifts[workerIndex]++;

            if (tryAssign(workerIndex + 1, assignedCount + 1)) {
                return true;
            }

            sched[day][assignedCount] = INVALID_ID;
            shifts[workerIndex]--;
        }

        return tryAssign(workerIndex + 1, assignedCount);
    };

    return tryAssign(0, 0);
}
