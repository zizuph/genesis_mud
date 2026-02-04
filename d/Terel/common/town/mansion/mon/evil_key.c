inherit "/std/monster";
inherit "/std/act/trigaction";

#include <ss_types.h>
#include <macros.h>
#include <money.h>

#define WEP "/d/Terel/common/town/mansion/obj/bsword"
#define KEY "/d/Terel/common/town/mansion/obj/vkey"
#define TO  this_object()

public void do_move();
public string get_room();

static string place="";
static int moved=0;

public void
init_living()
{
    ::init_living();
    if (moved == 0 && interactive(this_player())) {
        moved = 1;
        set_alarm(2.0, -1.0, do_move);
    }
}

public void
create_monster()
{
    if (!IS_CLONE) return;
   
    set_name("priest");
    set_race_name("human");
    set_short("evil priest");
    set_adj("evil");
    set_long("He is a very evil individual.  He wears a dark black " +
       "robe decorated with letters and inscriptions of the like " +
       "that you have never seen before.  He also carries a small " +
       "key.\n");
    set_living_name("rhundhi");

    default_config_npc(72);

    set_hp(9000);
    
    set_skill(SS_DEFENCE, 60);
    set_skill(SS_PARRY, 50);
    set_skill(SS_WEP_SWORD, 65);

    seq_new("do_things");
    seq_addfirst("do_things", ({"@@arm_me"}));

    set_chat_time(1);
    add_chat("Join forces with the EVIL ONE!  It is your destiny.\n");
    add_chat("One day, very soon, evil will reign high and mighty.\n");
    add_chat("You look like a good candidate.  Are you a virgin?\n");

    set_alignment(-500);
}

arm_me()
{
    seteuid(getuid());

    clone_object(WEP)->move(TO);
    clone_object(KEY)->move(TO);
    MONEY_MAKE_SC(10)->move(TO);
    
    command("wield sword");
}

public void
do_move()
{
   command("grin evilly");
   command("east");
   move_living("via the dumbwaiter", get_room());
}

public string
get_room()
{
   switch (random(12))
   {
   case  0: return "/d/Terel/common/town/mansion/grand";
   case  1: return "/d/Terel/common/town/mansion/rooms/bstairs_mid";
   case  2: return "/d/Terel/common/town/mansion/rooms/serv_quart";
   case  3: return "/d/Terel/common/town/mansion/rooms/wrkroom";
   case  4: return "/d/Terel/common/town/mansion/rooms/gameroom";
   case  5: return "/d/Terel/common/town/mansion/chapel/chapel";
   case  6: return "/d/Terel/common/town/mansion/lib/library_4";
   case  7: return "/d/Terel/common/town/mansion/lib/library_12";
   case  8: return "/d/Terel/common/town/mansion/tapestry_room";
   case  9: return "/d/Terel/LoD/corr11";
   case 10: return "/d/Terel/LoD/tunnel7";
   case 11: return "/d/Terel/common/town/mansion/graveyard/grv2";
   }
}
