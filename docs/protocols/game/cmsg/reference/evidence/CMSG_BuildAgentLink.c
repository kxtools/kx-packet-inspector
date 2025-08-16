// [OLD_NAME]: CMSG_Builder_AgentLink_0x0036
void CMSG::BuildAgentLink(longlong param_1,undefined8 *param_2)

{
  undefined4 uVar1;
  longlong lVar2;
  uint local_res8 [8];
  undefined1 local_48 [2];
  longlong local_46;
  undefined8 local_3e;
  short local_30;
  undefined2 local_2e;
  longlong local_28;
  undefined8 local_20;
  undefined4 local_18;
  
  local_46 = param_1 + 8;
  local_3e = *param_2;
  uVar1 = FUN_1409a35f0();
  local_2e = (undefined2)uVar1;
  local_18 = 0x100;
  local_20 = 0;
  local_28 = 0;
  local_30 = 1;
  lVar2 = MsgConn::BuildPacketFromSchema
                    (&local_30,(uint *)&DAT_142513080,0x12,(longlong)local_48,local_res8);
  if (lVar2 != 0) {
    MsgConn::QueuePacket(DAT_142628800,0,0x36,lVar2);
  }
  if (local_28 != 0) {
                    /* WARNING: Subroutine does not return */
    FUN_1409bf4b0(local_28);
  }
  return;
}

