// [OLD_NAME]: SMSG_PostParse_Handler_Type03FE
undefined8 Marker::Cli::ProcessAgentMarkerUpdate(undefined8 param_1,longlong param_2)

{
  longlong lVar1;
  undefined8 local_18;
  undefined4 local_10;
  undefined4 local_c;
  
  lVar1 = FUN_1413e12f0();
  local_18 = *(undefined8 *)(param_2 + 0xe);
  if (*(uint *)(param_2 + 6) != 0) {
    local_10 = *(undefined4 *)(param_2 + 0x16);
    local_c = *(undefined4 *)(param_2 + 0x1a);
    Gw2::Game::Marker::Cli::MkrCliContext
              (lVar1,*(uint *)(param_2 + 2),*(uint *)(param_2 + 6),&local_18,
               *(undefined4 *)(param_2 + 10));
    return 1;
  }
  local_10 = *(undefined4 *)(param_2 + 0x16);
  local_c = *(undefined4 *)(param_2 + 0x1a);
  Gw2::Game::Marker::Cli::MkrCliContext
            (lVar1,*(uint *)(param_2 + 2),&local_18,*(undefined4 *)(param_2 + 10),
             (uint)*(byte *)(param_2 + 0x1e));
  return 1;
}

