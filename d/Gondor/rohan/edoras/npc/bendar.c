/*
 * Gwyneth 4 November 2000 - Replaced ~elessar/lib/goodkill.h with
 *                           /d/Gondor/common/lib/logkill.c
 */
inherit "/std/monster";

#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include <living_desc.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/lib/logkill.c"

int     seq_c = 0,
        seq_alarm,
        intro_alarm;

void
create_monster() 
{
  set_living_name("bendar");
  set_name(({"bendar","shopkeeper","owner","shopowner"}));
  set_title("of Edoras, trader and shopkeeper");
  set_race_name("human");
  set_adj(({"stocky","dark-haired"}));
  set_long("This is Bendar the shopkeeper, who runs the General Store in Edoras.\n"+
    "He is probably quite competent with numbers - trade is his speciality.\n");
  default_config_npc(52);
  set_base_stat(SS_CON,95);
  set_base_stat(SS_STR,95);
  set_hp(2565);
  set_skill(SS_WEP_SWORD, random(10)+90);
  set_skill(SS_DEFENCE, random(10)+90);
  set_skill(SS_PARRY, random(10)+90);
  set_alignment(100+random(200));
  set_chat_time(12);
  add_chat("Can I help you?");
  add_chat("Welcome to my shop!");
  add_chat("My name is Bendar.");
  add_chat("Have you got anything nice to sell?");
  add_chat("Perhaps you want to buy some excellent equipment?");
  add_cchat("Get out of here, you thieving scoundrel!");
  add_cchat("You won't get away with this, you know!");
  add_cchat("Guards! Help!");
  seq_new("do_things");
  seq_addfirst("do_things",({"@@get_armed","say Well, I'm back in business.","present me"}));  
}

void
get_armed()
{
  FIX_EUID
  clone_object(EDORAS_DIR + "obj/broadsword")->move(TO);
  command("wield sword");
  clone_object(EDORAS_DIR + "obj/leather")->move(TO);
  command("wear armour");
}

/* solemnian prestige */
query_knight_prestige() {return (-5);}

void
open_shop()
{
    if (objectp(query_attack()))
        return;

    seq_c = 0;
    seq_alarm = set_alarm(5.0, 1.0, "open_shop_seq");
}

void
open_shop_seq()
{

    switch(seq_c++)
    {
        case 0: 
            command("e");
            break;
        case 1:
            command("present me");
            break;
        case 2:
            command("say The Store is open now!");
            break;
        case 3:
            break;
        case 4:
            command("yawn");
            break;
        case 5:
            command("say Beautiful morning, isn't it?");
            break;
        case 6:
            break;
        case 7:
            command("stretch");
            break;
        case 8:
            break;
        case 9:
            command("say Well, off to work!");
            break;
        case 10:
            command("smile cheerfully");
            break;
        case 11:
            break;
        case 12:
            command("w");
            break;
        default:
            remove_alarm(seq_alarm);
            break;
    }
}

public void
add_introduced(string str)
{
    object  pl;

    if (!objectp(pl = find_player(str)))
        return;

    if (pl->query_met(query_real_name()))
        return;

    if (intro_alarm && sizeof(get_alarm(intro_alarm)))
        return;

    intro_alarm = set_alarm(2.0, 0.0, &command("introduce me to "+str));
}

