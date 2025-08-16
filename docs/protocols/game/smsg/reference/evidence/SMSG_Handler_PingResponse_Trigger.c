
undefined8 SMSG_Handler_PingResponse_Trigger(undefined8 param_1,longlong param_2)

{
  CMSG::BuildPingResponse(*(uint *)(param_2 + 2));
  return 1;
}

