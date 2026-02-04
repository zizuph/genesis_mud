/* A courier. Mortricia 931111 */
inherit "/std/monster";

#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <money.h>

#define DIR      "/d/Terel/"
#define TDIR     (DIR+"common/town/")
#define MDIR     "/d/Terel/mortricia/"
#define PORT_DIR (DIR + "port/")

#define TO       this_object()

#define ROOMS ({\
		({DIR+"port/wpier_s"}),\
	        ({TDIR+"road_e/road_e08"}),\
		({TDIR+"square1_4", TDIR+"road_e/road_e01"}),\
		({TDIR+"square1_1", TDIR+"square1_2"}),\
		({TDIR+"square4_1"}),\
		({TDIR+"square1_1", TDIR+"square2_1"}),\
		({TDIR+"square1_4", TDIR+"square1_3"}),\
		({TDIR+"road_s/road_s11", TDIR+"road_s/road_s10"}),\
		({TDIR+"road_s/road_s11", MDIR+"camp/entrance"})\
	      })
#define CMDS ({\
	      ({"cmd halt", "dismount", "smile samlon",\
		"whisper samlon bla bla...", "wave samlon",\
		"mount abra", "cmd n quickly"}),\
	      ({"cmd halt", "cmd w gently"}),\
	      ({"cmd halt", "cmd n slowly"}),\
	      ({"cmd halt", "cmd e slowly"}),\
	      ({"cmd halt", "dismount", "east", "look at board", "ponder",\
		"say Hmm... I better bring this message to Samlon",\
		"west", "mount abra", "cmd w slowly"}),\
	      ({"cmd halt", "cmd s slowly"}),\
	      ({"cmd halt", "cmd se", "cmd s quickly"}),\
	      ({"cmd halt", "cmd w", "cmd w", "cmd n",\
		"dismount", "west", "buy beer", "drink beer",\
		"say Ahh! I really needed that!", "wave",\
		"north", "buy pirogue", "eat pirogue", "buy hay",\
		"south", "east", "feed abra with hay",\
		"mount abra", "cmd s", "cmd e slowly"}),\
	      ({"cmd halt", "cmd s quickly"})\
	     })
#define START ({"wear cloak", "wield sword", "name horse abra",\
		"mount abra", "cmd n quickly"})

public void horse_cmd(object to, object from);
public void do_cmds(string *cmds);

public void
create_monster()
{
    set_name("courier");
    add_name("messenger");
    set_short("bow-legged courier");
    set_long(break_string(
	"It is a courier of some kind. His clothes look rather " +
	"dusty. He is probably on a messenger mission.\n", 70));
    set_adj("bow-legged");
    set_race_name("human");
    set_gender(0);
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(LIVE_I_QUICKNESS, 70);

    set_stats(({70,70,70,55,55,60}));
    set_hp(9999);
    set_mana(9999);
    set_alignment(100);
    set_skill(SS_DEFENCE, 75 + random(11));
    set_skill(SS_UNARM_COMBAT, 50 + random(11));
    set_skill(SS_PARRY, 75 + random(11));
    set_skill(SS_WEP_SWORD, 75 + random(11));
    set_skill(SS_ANI_HANDL, 99);
    set_skill(SS_AWARENESS, 99);

    set_all_hitloc_unarmed(45);
    set_all_attack_unarmed(35, 35);

    seteuid(getuid());
    MONEY_MAKE_GC(10)->move(this_object());

    seq_new("do_stream");
    seq_addfirst("do_stream", ({"@@dress_me"}));
}

public void
dress_me()
{
    object bag;

    seteuid(getuid());
    
    clone_object(PORT_DIR + "armour/c_cloak")->move(TO);
    clone_object(PORT_DIR + "weapon/c_sword")->move(TO);
    bag = clone_object(PORT_DIR + "obj/l_bag");
    bag->move(TO);

    do_cmds(START);
}

public void
horse_cmd(object to, object from)
{
    int i, cmd_no = -1;

    if (!to || !from) return;

    for (i=0; i<sizeof(ROOMS); i++) {
	if (file_name(to) == ROOMS[i][0]) {
	    if (sizeof(ROOMS[i]) > 1 &&
		file_name(from) != ROOMS[i][1]) continue;
	    cmd_no = i;
	    break;
	}
    }

    if (cmd_no < 0) return;

    do_cmds(CMDS[cmd_no]);
}

public void
do_cmds(string *cmds)
{
    int j;

    for (j=0; j<sizeof(cmds); j++) {
	if (j==0) 
	    command(cmds[0]);
	else
	    set_alarm(itof(4*j), -1.0, &command(cmds[j]));
    }
}
