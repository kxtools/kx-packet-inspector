// [NEW_NAME]: CMSG_Skill_CommandHandler (FUN_1410168c0)
// Purpose: This is the top-level handler for a skill-use command. It retrieves
// the appropriate skill manager object and then calls the "Pre-Aggregator"
// function to continue the packet building process. This represents the highest
// level in the CMSG skill-use pipeline.

void CMSG_Skill_CommandHandler(longlong param_1,longlong *param_2)
{
  longlong *plVar1;
  bool bVar2;
  undefined7 extraout_var;
  int local_res8 [2];
  
  plVar1 = *(longlong **)(*(longlong *)(param_1 + 0x20) + 0x10);
  if (plVar1 != (longlong *)0x0) {
    local_res8[0] = 1;
    // Calls a virtual method on the skill manager to prepare data
    (**(code **)(*plVar1 + 0xc0))(plVar1,(int)param_2[10],param_2 + 5,local_res8);
    bVar2 = FUN_1410131f0(*(longlong *)(param_1 + 0x90));
    if (((int)CONCAT71(extraout_var,bVar2) != 0) && (local_res8[0] == 0)) {
      return;
    }
  }
  
  // Calls the next function in the chain (the Pre-Aggregator)
  FUN_1410225a0(param_2);
}