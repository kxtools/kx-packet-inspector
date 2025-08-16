
void Gw2::Game::Chat::Cli::CtCliContext
               (longlong *param_1,ulonglong param_2,LPCWSTR param_3,ulonglong param_4,uint param_5)

{
  bool bVar1;
  int iVar2;
  undefined8 uVar3;
  undefined7 extraout_var;
  undefined1 auStack_68 [32];
  undefined8 local_48 [2];
  ulonglong local_38;
  
  local_38 = DAT_142551900 ^ (ulonglong)auStack_68;
  iVar2 = FUN_1412a6ab0(param_3,param_2,param_3,param_4);
  if (iVar2 == 0) {
    uVar3 = FUN_1409ab650(param_3);
    if ((int)uVar3 != 0) {
                    /* WARNING: Subroutine does not return */
      FUN_1409cd550();
    }
    bVar1 = FUN_14128a2b0((uint)param_2);
    if ((int)CONCAT71(extraout_var,bVar1) == 0) {
      Gw2::Services::Msg::Msg(param_3,(uint)param_2,(int)param_4,param_5);
    }
    else {
      (**(code **)(*param_1 + 0x150))(param_1,local_48,param_2 & 0xffffffff);
      Gw2::Services::Msg::Msg(param_3,local_48,(int)param_4,param_5);
    }
  }
                    /* WARNING: Subroutine does not return */
  FUN_140e37790(local_38 ^ (ulonglong)auStack_68);
}

