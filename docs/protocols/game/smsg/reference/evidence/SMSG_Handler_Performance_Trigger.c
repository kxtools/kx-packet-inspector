
void SMSG_Handler_Performance_Trigger
               (undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4)

{
  ulonglong uVar1;
  ushort local_res18;
  undefined4 local_res1a;
  
  uVar1 = GrPerf::GetCounterValue(4,3,param_3,param_4);
  if ((int)uVar1 == 0) {
    local_res1a = 0x28;
  }
  else {
    local_res1a = (undefined4)(1000 / (uVar1 & 0xffffffff));
  }
  local_res18 = 2;
                    /* WARNING: Subroutine does not return */
  CMSG::BuildAndSendPacket(DAT_142628290,6,&local_res18);
}

