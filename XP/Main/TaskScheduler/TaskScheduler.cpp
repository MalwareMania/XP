#include "TaskScheduler.hpp"

uintptr_t Scheduler::get_job_by_name(const std::string& name) {
    uintptr_t raw_scheduler = *(uintptr_t*)Offsets::RawScheduler; // read the task scheduler
    uintptr_t jobStart = *(uintptr_t*)(raw_scheduler + Offsets::TaskScheduler::JobStart); // get the start of the job list by adding the task scheduler + jobstart offset
    uintptr_t jobEnd = *(uintptr_t*)(raw_scheduler + Offsets::TaskScheduler::JobEnd); // or JobStart + sizeof(void*) // get the job end offset

    for (auto i = jobStart; i < jobEnd; i += 0x10) // loop through each job, the spacing between them is 0x10
    {
        uintptr_t jobAddress = *(uintptr_t*)i; // convert to job address

        std::string* jobName = (std::string*)(jobAddress + Offsets::TaskScheduler::JobName); // read job name as std::string
        if (jobName && *jobName == name) // see if the jobname matches with the "name" arg and return the job address as is
        {
            return jobAddress;
        }
    }
    return 0;
}

uintptr_t Scheduler::get_data_model()
{
    uintptr_t fakeDM = *(uintptr_t*)Offsets::DataModel::FakeDataModelPointer;

    return *(uintptr_t*)(fakeDM + Offsets::DataModel::FakeDataModelToDataModel);
}

uintptr_t Scheduler::get_script_context()
{
    uintptr_t children = *(uintptr_t*)(*(uintptr_t*)(get_data_model() + Offsets::DataModel::Children)); 

    return *(uintptr_t*)(children + Offsets::DataModel::ScriptContext);
}

lua_State* Scheduler::get_lua_state()
{
    int32_t ignore = 2;
    uintptr_t ignore1 = { 0 };
    uintptr_t Gs = Roblox::GetGlobalState(get_script_context() + Offsets::LuaState::GlobalState, &ignore, &ignore1);
    xp_globals::xp_state = lua_newthread((lua_State*)(Roblox::DecryptState(Gs + Offsets::LuaState::DecryptState)));

    return xp_globals::xp_state;
}
