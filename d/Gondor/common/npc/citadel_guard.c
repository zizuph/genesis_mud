/*
 * Modified - Gwyneth (Nov 4, 2000) replaced ~elessar/lib/goodkill.h
 *            with /d/Gondor/common/lib/logkill.c
 */
inherit "/std/monster";
#include "/d/Gondor/common/lib/logkill.c"

#include "/sys/ss_types.h"
#include "/sys/macros.h"

create_monster()
{
  if (!IS_CLONE)
    return;
  set_name(({"guard","cityguard","guard of the citadel"}));
  set_race_name("human");
  set_short("strong guard");
  set_long("This guard is one of the Guards of the Citadel. He is robed in black,\n"+
    "and has a strange, high-crowned helmet with wings of seabirds set above\n"+
    "some long, close-fitting cheek-guards. Upon his black surcoat you can\n"+
    "see the embroidered image of a white tree in blossom beneath a silver\n"+
    "crown and many-pointed stars. This is the emblem of the heirs of Elendil,\n"+
    "and none except the Guards of the Citadel wear it now.\n");
  set_adj(({"tall","strong"}));
  set_pshort("strong guards");
  set_alignment(400+random(80));
  default_config_npc(random(10)+58);
  set_base_stat(SS_CON,random(10)+62);
  set_hp(10000);
  set_skill(SS_WEP_SWORD, random(10)+70);
  set_skill(SS_WEP_POLEARM, random(10)+80);
  set_skill(SS_PARRY,85);
  set_skill(SS_DEFENCE,85);
  set_chat_time(16);
  add_chat("Looks like the War is drawing nigh.");
  add_chat("What are you hanging around here for?");
  add_chat("Minas Tirith is a well-guarded city.");
  add_chat("I am with the Guards of the Citadel.");
  add_chat("I don't like the dark clouds gathering in the east.");
  seq_new("do_things");
  seq_addfirst("do_things",({"@@get_armed","say Reporting for guard-duty!"}));
}

get_armed() {
  object wep, arm;
  seteuid(getuid(this_object()));
  wep = clone_object("/d/Gondor/common/wep/halberd");
  wep->move(this_object());
  command("wield halberd");
  arm = clone_object("/d/Gondor/common/obj/dsurcoat");
  arm->move(this_object());
  command("wear surcoat");
  arm = clone_object("/d/Gondor/common/arm/winghelm");
  arm->move(this_object());
  command("wear helm");
}

/* Knights will loose prestige on this one */
query_knight_prestige() { return -8; }

