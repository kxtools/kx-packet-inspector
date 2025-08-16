// [NEW_NAME]: PlayerAction_DataAggregator (FUN_14101f990)
// Purpose: A high-level function that gathers all necessary player state data
// (position, flags, IDs, etc.) for various player actions and packages it into
// a temporary structure on the stack. It then makes a virtual call to a
// specialized builder function, passing the aggregated data to be serialized and sent.

void PlayerAction_DataAggregator(longlong param_1,int param_2,undefined8 *param_3)
{
  undefined2 local_58;
  undefined2 local_56;
  undefined4 local_54;
  undefined1 local_50;
  undefined4 local_4f;
  undefined1 local_4b;
  longlong *local_4a;
  undefined8 *local_42;
  undefined8 local_38;
  undefined8 uStack_30;
  uint local_28;
  float *local_24;
  float *local_1c;
  undefined1 local_14;
  undefined1 local_13;
  
  local_58 = 0x34;
  if (param_2 == 1) {
    local_58 = 9; // Sets the opcode to 0x0009 for a JUMP action
  }
  local_56 = *(undefined2 *)(*(longlong *)(*(longlong *)(param_1 + 0x20) + 0x20) + 0xc);
  local_54 = *(undefined4 *)(*(longlong *)(param_1 + 0x58) + 0x1d0);
  local_50 = *(undefined1 *)(param_1 + 0x50);
  local_4f = *(undefined4 *)(param_1 + 0x28);
  local_4b = *(undefined1 *)(param_1 + 0x2c);
  local_4a = FUN_141008200(param_1 + 0x28);
  if (*(int *)(param_1 + 0xac) != 0) {
    local_38 = *(undefined8 *)(param_1 + 0x70);
    uStack_30 = *(undefined8 *)(param_1 + 0x78);
    local_28 = 0;
    if ((*(uint *)(param_1 + 0x80) >> 0x1e & 1) != 0) {
      local_28 = *(uint *)(param_1 + 0x80);
    }
    if ((((*(float *)(param_1 + 0x84) != 0.0) || (*(float *)(param_1 + 0x88) != 0.0)) ||
        (*(float *)(param_1 + 0x8c) != 0.0)) ||
       (local_24 = (float *)0x0, *(float *)(param_1 + 0x90) != 0.0)) {
      local_24 = (float *)(param_1 + 0x84);
    }
    if (((*(float *)(param_1 + 0x94) != 0.0) || (*(float *)(param_1 + 0x98) != 0.0)) ||
       ((*(float *)(param_1 + 0x9c) != 0.0 ||
        (local_1c = (float *)0x0, *(float *)(param_1 + 0xa0) != 0.0)))) {
      local_1c = (float *)(param_1 + 0x94);
    }
    local_14 = *(undefined1 *)(param_1 + 0xa4);
    local_13 = *(undefined1 *)(param_1 + 0xa5);
  }
  local_42 = &local_38;
  if (*(int *)(param_1 + 0xac) == 0) {
    local_42 = (undefined8 *)0x0;
  }
  
  // Makes the virtual call to the final builder function (e.g., CMSG_Builder_FromAggregatedData)
  (**(code **)*param_3)(param_3,*(undefined4 *)(param_1 + 0x50),0x1e,&local_58);
  return;
}
