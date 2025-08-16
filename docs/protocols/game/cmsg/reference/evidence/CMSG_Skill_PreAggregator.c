// [NEW_NAME]: CMSG_Skill_PreAggregator (FUN_1410225a0)
// Purpose: This function acts as a gate for skill commands. It performs
// validation checks and, if they pass, explicitly loads a pointer to the
// generic builder (`CMSG_Builder_FromAggregatedData`). It then calls the
// true data aggregator (via a virtual function call), passing it the
// pointer to the generic builder to use.

void CMSG_Skill_PreAggregator(longlong *param_1)
{
  bool bVar1;
  undefined7 extraout_var;
  undefined **local_res8 [4];
  
  // Performs validation checks on the skill data
  if ((*(uint *)(param_1 + 10) & 0x400000) != 0) {
    bVar1 = FUN_1410131d0(param_1[0xb]);
    if ((int)CONCAT71(extraout_var,bVar1) != 0) {
    
      // THE SMOKING GUN: Explicitly loads the address of the generic builder
      local_res8[0] = &PTR_CMSG_Builder_FromAggregatedData_1420e8e00;
      
      // Makes a virtual call to the true data aggregator, passing it the builder pointer
      (**(code **)(*param_1 + 0x30))(param_1,1,local_res8);
    }
  }
  return;
}