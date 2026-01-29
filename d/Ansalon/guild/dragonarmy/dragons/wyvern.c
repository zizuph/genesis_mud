/*
 * Louie 2005
 * Wyvern copied from Dragonsteed code for the Dragonarmies
 *
 * Navarre July 3rd 2006, moved .\n into the passenger description, else we risk getting two
 * periods when the wyvern is not occupied.
 * Fixed damage description message. Excluded ob from tell room and added ob->catch_msg
 */
#pragma strict_types
#pragma save_binary

inherit "/std/creature";
inherit "/std/combat/unarmed";

#include "../guild.h"

#include <macros.h>
#include <composite.h>
#include <cmdparse.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <wa_types.h>
#include <filter_funs.h>

#define WYVERN_POISON  (DRAGONARMY_DRAGON+"wyvern_poison")

static object back, msg_relay;
int size, fight = 0, restless = 0, alarm = 0;
private object summoner;
int *teeth, *claw, *wing, *skin;
string w_size = "small";
string w_adj;
string *adj = ({ "vicious","cruel","savage","wicked", 
    "black","brown","malicious","malevolent","horrid", 
    "hateful","brutal","bloodthirsty","nefarious","vile" });
string *tail_hit_how = ({"uninjured","barely stung","slightly stung", 
                        "stung","painfully stung","deeply stung" });

/*proto*/
void setup_wyvern();
string long_desc();
string short_desc();
void set_wyvern_size(string str);
void set_summoner(object ob);
object query_summoner();
string query_wyvern_size();
void check_back();
string passenger_desc();
public int try_set_summoner(string str);
public object * query_wyvern_occupied();
void check_stick_around();
/**/

void
create_creature()
{
    seteuid(getuid());

    add_name("wyvern");
    set_race_name("wyvern");
    set_gender(random(2));
    w_adj = adj[random(sizeof(adj))];
    add_adj(w_adj);

    set_long("@@long_desc");
    set_short("@@short_desc");

    set_skill(SS_DEFENCE, 90);
    set_skill(SS_UNARM_COMBAT, 90);
    set_skill(SS_AWARENESS, 50);
    set_alignment(-200 - random(600));

    setup_wyvern();

    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(OBJ_M_NO_ATTACK, "@@wyvernsteed_no_attack");
    add_prop("_live_i_no_dragonfear", 1);
    
    msg_relay = clone_object(DRAGONARMY_DRAGON + "msg_relay2");
    msg_relay->set_dragon(TO);
    //  set_alarm(45.0, 0.0, leave_area);
    set_alarm(0.0, 0.0, check_back);
    set_alarm(1800.0, 0.0, &check_stick_around());

     /* Setting the attack and armour values for the wyverns */
    set_attack_unarmed(0, teeth[0], teeth[1], W_IMPALE, 30, "bite");
    set_attack_unarmed(1, wing[0], wing[1], W_BLUDGEON, 15, "right wing");
    set_attack_unarmed(2, wing[0], wing[1], W_BLUDGEON, 15, "left wing");
    set_attack_unarmed(3, claw[0], claw[1], W_SLASH, 45, "right claw");
    set_attack_unarmed(4, claw[0], claw[1], W_SLASH, 45, "left claw");

    set_hitloc_unarmed(0, skin[0], 20, "head");
    set_hitloc_unarmed(1, skin[1], 40, "body");
    set_hitloc_unarmed(2, skin[2], 25, "tail");
    set_hitloc_unarmed(3, skin[3], 14, "wing");
    set_hitloc_unarmed(4, skin[4], 1, "belly");

    add_prop(NPC_I_NO_RUN_AWAY, 1);
    add_prop(NPC_I_NO_LOOKS, 1);
}

string
long_desc()
{
     return capitalize(LANG_ADDART(short())) +
         " looms before you, a less intelligent "+
         "and more beastial relative of the mighty dragons.  "+
         "Some wyvern may occasionally be trained to serve as "+
         "mounts.  "+
         passenger_desc();
}

void
check_stick_around()
{
    int i;
    object *arr = query_wyvern_occupied();

    if (objectp(summoner) ||
        MASTER_OB(E(TO)) == TEMP_DRAGON_ROOM) {
            set_alarm(1800.0, 0.0, &check_stick_around());
        return;
    }

    for (i = 0; i < sizeof(arr); i++)
    {
	    if (!living(arr[i]))
    	    continue;

	    if (interactive(arr[i]) || arr[i]->query_npc())
	    {
    	    arr[i]->command("$dismount wyvern");
	        continue;
	    }

	    arr[i]->move_living("M", OWN_STATUE, 1);
	    OWN_STATUE->set_revive_dest(arr[i], file_name(E(TO)));
    }

    move_living("into the sky", TEMP_DRAGON_ROOM, 1, 1);
    remove_object();
}

string
short_desc()
{
    return w_size+" "+w_adj+" wyvern";
}

void
set_wyvern_size(string str)
{
    if (w_size == str)
        return;

    remove_adj(w_size);
    
    w_size = str;

    setup_wyvern();
}

void
setup_wyvern()
{
    int i;
    switch (w_size) {
        case "small":
            set_adj("small");
            for(i = 0; i < 6; i++)
                set_base_stat(i, 100 + random(15));
            break;
        case "large":
            set_adj("large");
            for(i = 0; i < 6; i++)
                set_base_stat(i, 110 + random(25));
            break;
        default:
            set_adj("small");
            for(i = 0; i < 6; i++)
                set_base_stat(i, 100 + random(15));
            break;
    }
    teeth = ({ 65, 65 });
    claw = ({ 75, 55 });
    wing = ({ 55, 45 });
    skin = ({ 75, 85, 65, 65, 45 });
}

object
query_msg_relay()
{
    return msg_relay;
}

void
set_summoner(object ob)
{
    summoner = ob;

}

object
query_summoner()
{
    return summoner;
}

string
query_wyvern_size()
{
    return w_size;
}

public object *
query_wyvern_occupied()
{
    return back->query_wyvern_occupied();
}

void
check_back()
{
    if (!back)
    {
	setuid();
	seteuid(getuid());
	back = clone_object(DRAGONARMY_DRAGON + "wyvern_back");
	back->set_wyvern(TO);
    }
}

object
query_back()
{
    return back;
}

string
passenger_desc()
{
    int i;
    object *pas = query_wyvern_occupied();

    switch(sizeof(pas))
    {
    case 0:
	return "";
    default:
	return capitalize(HE(TO))+" has "+COMPOSITE_LIVE(pas)+" mounted on "+HIM(TO)+".\n";
    }
}

mixed
wyvernsteed_no_attack()
{
    if(back->query_flying())
	return "You have no way to attack a flying wyvern.\n";
    return 0;
}

int
special_attack(object enemy)
{
    mixed* hitresult;
    object ob, poison;
    string how_str;

    if (TO->query_wyvern_size() == "small") {
        /*
        tell_room(E(TO),"**WYVERN is small so no special**\n");
        */
        return 0;
    }

    if (random(10)) {
        /*
        tell_room(E(TO),"**WYVERN failed random so no special**\n");
        */
        return 0;
    }

    if (!(ob = TO->query_attack())) {
        /*
        tell_room(E(TO),"**WYVERN has no enemy so no special**\n");
        */
        return 0;
    }

    tell_room(E(TO), QCTNAME(TO)+"'s tail quickly strikes out at "+
        QTNAME(ob)+"!\n", TO, ob);
    ob->catch_msg(QCTNAME(TO)+"'s tail quickly strikes out at you!\n");

    hitresult = ob->hit_me(400, W_IMPALE, TO, -1);

    how_str = tail_hit_how[0];
    if (hitresult[0] > 0)
        how_str = tail_hit_how[1];
    if (hitresult[0] > 10)
        how_str = tail_hit_how[2];
    if (hitresult[0] > 20)
        how_str = tail_hit_how[3];
    if (hitresult[0] > 40)
        how_str = tail_hit_how[4];
    if (hitresult[0] > 60)
        how_str = tail_hit_how[5];

    ob->catch_msg("You are "+how_str+" by the "+short()+"'s tail!\n");
        tell_watcher(QCTNAME(ob) + " is "+how_str+" by the "+short()+ 
            "'s tail!\n", ob);

    if (ob->query_hp() <= 0)
        ob->do_die(TO);

    if (hitresult[0] > 20) {
        poison = clone_object(WYVERN_POISON);
        poison->move(ob);
        poison->start_poison(TO);
    }

    return 1;

}

public int
try_set_summoner(string str)
{
    object pl;

    if (!strlen(str) || !TP->query_wiz_level()
        || !(pl = find_player(str))) {
            NF("Didn't work.\n");
            return 0;
    }

    set_summoner(pl);
    write("Summoner set.\n");
    return 1;
}

public int
mount(string str)
{
    mixed *oblist;

    if (!strlen(str) ||
      !parse_command(str, all_inventory(E(TP)),	"[the] %i", oblist) ||
      !sizeof(oblist = NORMAL_ACCESS(oblist, 0, 0)))
    {
	NF(C(query_verb()) + " what?\n");
	return 0;
    }

    if (sizeof(oblist) > 1)
    {
	NF(C(query_verb()) + " what?  Be more specific.\n");
	return 0;
    }

    if(!oblist[0]->dragonarmy_wyvern_mount())
    {
	NF("You can't seem to mount that.\n");
	return 0;
    }

    return 1;
}

public int
dragonarmy_wyvern_mount()
{
    check_back();

    if (TP->query_prop("_wolf_i_riding"))
    {
	write("Mount a wyvern while riding a wolf? Nonsense!\n");
	return 1;
    }

    if (TP != summoner && !present(summoner, back))
    {
	write("The "+short()+" turns to you and snarls as you attempt " +
	  "to mount it, making it very clear that you are not a " +
	  "welcome passenger without its summoner.\n");
	return 1;
    }

    if ((sizeof(query_wyvern_occupied()) > 0
        && query_wyvern_size() == "small") ||
        sizeof(query_wyvern_occupied()) > 1)
    {
	write("There is no space left for you on the "+short()+".\n");
	return 1;
    }
    if (TP != summoner &&
      member_array(TP, summoner->query_team_others()) < 0 &&
      TP->query_prop("_da_can_mount_wyvern") != TO)
    {
	write("The "+short()+" turns to you and snarls as you attempt " +
	  "to mount it, making it very clear that only " +
	  "its riders teammates and invited guests are welcome passengers.\n");
	return 1;
    }

    say(({METNAME+ " mounts the "+short()+".\n",
	NONMETNAME+ " mounts the "+short()+".\n",
	"" }));
    write("You mount the "+short()+".\n");
    TP->move_living("M", back, 1);
    return 1;
}

void
init_living()
{
    ::init_living();
    add_action(mount, "mount");
    add_action(try_set_summoner, "set_summoner");
}

public void
remove_object()
{
    msg_relay->remove_object();
    back->remove_object();
    ::remove_object();
}

public int
query_dragonarmy_wyvern()
{
    return 1;
}

int
move(mixed dest, mixed subloc)
{
    int result = ::move(dest, subloc);
    msg_relay->move(E(TO), 1);

    /*
    restless = 0;
    if (alarm)
    {
	remove_alarm(alarm);
	alarm = 0;
    }

    if (MASTER_OB(E(TO)) != TEMP_DRAGON_ROOM)
    {
	alarm = set_alarm(45.0, 0.0, leave_area);
    }
    */
    return result;
}
/*
public void
leave_area()
{
    int i;
    object *arr = query_wyvern_occupied();

    if ((member_array(summoner, arr) > -1) && !restless)
    {
	restless = 1;
	summoner->catch_tell("Your wyvern is growing restless.\n"+
	  "It will fly away soon alone if you do not command him to destination.\n");
	alarm = set_alarm(15.0, 0.0, leave_area);
	return;
    }

    for (i = 0; i < sizeof(arr); i++)
    {
	if (!living(arr[i]))
	    continue;

	if (interactive(arr[i]) || arr[i]->query_npc())
	{
	    arr[i]->command("$dismount dragon");
	    continue;
	}

	arr[i]->move_living("M", OWN_STATUE, 1);
	OWN_STATUE->set_revive_dest(arr[i], file_name(E(TO)));
    }

    move_living("into the sky", TEMP_DRAGON_ROOM, 1, 1);
    remove_object();
}

public void
leave_area_fight()
{
    int i;
    object *arr = filter(FILTER_LIVE(all_inventory(E(TO))), check_fighting);

    if (!sizeof(arr))
    {
	fight = 0;
	set_alarm(5.0, 0.0, leave_area_fight);
	return;
    }

    arr = query_dragon_occupied();
    if ((member_array(summoner, arr) > -1) && !fight)
    {
	fight = 1;
	set_alarm(5.0, 0.0, leave_area_fight);
	return;
    }

    for (i = 0; i < sizeof(arr); i++)
    {
	if (!living(arr[i]))
	    continue;

	if (interactive(arr[i]) || arr[i]->query_npc())
	{
	    arr[i]->command("$dismount dragon");
	    continue;
	}

	arr[i]->move_living("M", OWN_STATUE, 1);
	OWN_STATUE->set_revive_dest(arr[i], file_name(E(TO)));
    }

    move_living("into the sky", TEMP_DRAGON_ROOM, 1, 1);
    remove_object();
}

private int
check_fighting(object ob)
{
    return !!ob->query_attack();
}

*/
