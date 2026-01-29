#pragma strict_types

#include "/d/Kalad/defs.h"
#include "../default.h"

#include <tasks.h>

inherit KALAD(steed/steed.c);

static string owner;
static int alarm;

public void
set_owner(object ob)
{
    owner = ob->query_real_name();
}

public string
query_owner()
{
    return owner;
}


string
steed_short()
{
    string* adjs = query_adj(1);
    if(sizeof(adjs) > 1)
        return adjs[0] +" "+adjs[1]+" wolf";
    return adjs[0] + " wolf";
}
public void
set_wolf_desc(string adj1, string adj2)
{
    if(stringp(adj1))
    {
	switch(adj1)
	{
	case "male":
	    set_gender(G_MALE);
	    add_adj(adj1);
	    adj1 = (string)0;
	    break;
	case "female":
	    set_gender(G_FEMALE);
	    add_adj(adj1);
	    adj1 = (string)0;
	    break;
	default:
	    add_adj(adj1);
	    break;
	}
    }
    if(stringp(adj2))
    {
	switch(adj2)
	{
	case "male":
	    set_gender(G_MALE);
	    add_adj(adj2);
	    adj2 = (string)0;
	    break;
	case "female":
	    set_gender(G_FEMALE);
	    add_adj(adj2);
	    adj2 = (string)0;
	    break;
	default:
	    add_adj(adj2);
	    break;
	}
    }

    if(strlen(adj1) && strlen(adj2))
	set_short(adj1+" "+adj2+" wolf");
    else if(strlen(adj1))
	set_short(adj1+" wolf");
    else if(strlen(adj2))
	set_short(adj2+" wolf");
    else
	set_short("wolf");
}

public int
configure_wolf(object me)
{
    string adjs,ad1,ad2;
    mapping temp = ([]);
    temp = restore_map(FANG_DIR(doc/wolf_log));
    adjs = temp[me->query_real_name()];
    if(!stringp(adjs))
	return 0;
    sscanf(adjs,"%s|%s",ad1,ad2);
    set_wolf_desc(ad1,ad2);
    set_owner(me);
    return 1;
}

public void
save_wolf()
{
    string *adjs = query_adjs();
    int     size = sizeof(adjs);
    mapping temp = restore_map(FANG_DIR(doc/wolf_log));

    if (size > 2)
    {
	adjs = slice_array(adjs, 1, 2);
    }

    if (size == 1)
    {
	temp[query_owner()] = adjs[0] + "|";
    }
    else
    {
	temp[query_owner()] = implode(adjs, "|");
    }
    save_map(temp, FANG_DIR(doc/wolf_log));
}

public varargs mixed
long(string str, object for_obj)
{
    string tmp = ::long(str, for_obj);

    if (str)
    {
	return tmp;
    }

    if (IS_MEMBER(this_player()) &&
      (this_player()->query_real_name() == query_owner()))
    {
	tmp += "If you are skilled, perhaps you can 'mount' it and "+
	"move around. If it gets tired or hungry, you can give "+
	"it food and it will eat it.\nTry wolfhelp for more "+
	"info.\n";
    }

    return tmp;
}

public int
st_hook_try_mount(object who)
{
    int res;

    if(who->query_skill(SS_WOLF_RIDING) < 1)
    {
	return 0;
    }

    res = who->resolve_task(TASK_ROUTINE, ({ TS_DEX, SS_WOLF_RIDING }));
    return (res > 0);
}

public void
st_hook_fail_mount(object who)
{

    if(who->query_skill(SS_WOLF_RIDING) < 1)
    {
	write("You have no idea how to ride such a beast.\n");
	say(QCTNAME(who)+" tries to mount a wolf, but has no idea how "+
	  "to ride one.\n");
	return;
    }

    switch(random(3))
    {
    case 0:
	write("You try to mount the wolf, but fall off again. Perhaps "+
	  "its time to improve your ability to ride wolves.\n");
	say(QCTNAME(who)+" tries to mount the wolf but falls on "+
	  who->query_possessive()+" butt!\n");
	who->command("blush");
	break;
    case 1:
	write("You accidentaly step on the wolf's foot while trying to "+
	  "mount him, and he snarls at you and kicks you.  Ouch!!\n");
	write("Perhaps its time to improve your ability to ride wolves.\n");
	say(QCTNAME(who)+" accidentaly steps on the wolf's foot while "+
	  "trying to mount it, and it snarls at "+HIM(who)+" and kicks "+
	  HIM(who)+".\n");
	who->command("blush");
	break;
    case 2:
	write("You try to mount the ferocious wolf, but you accidentally "+
	  "step over too far and fall down the other side.\n");
	write("Perhaps its time to improve some skill.\n");
	say(QCTNAME(who)+" tries to mount the wolf, but accidentally "+
	  "steps over too far and falls down the other side.\n");
	who->command("blush");
	break;
    }
}



public void
create_steed()
{
    set_steed_no_trans(0);
    set_steed_allow_combat(1);
    set_steed_skill(SS_WOLF_RIDING);
    set_steed_invalid_dest( ({ ROOM_I_NO_ALLOW_STEED }) );

    set_name("wolf");
    set_race_name("wolf");
    set_long("This is a strong and ferocious looking wolf. Bred by "+
      "goblins as a steed, it looks quite powerful. Only goblins would "+
      "know how to ride such a creature. It growls and stares at you "+
      "with fierce blood-shot eyes.\n");

    set_stats( ({ 120, 120, 120, 20, 20, 100 }) );

    set_skill(SS_CLIMB,        30);
    set_skill(SS_SWIM,         20);
    set_skill(SS_SNEAK,        50);
    set_skill(SS_HIDE,         50);
    set_skill(SS_AWARENESS,    50);
    set_skill(SS_UNARM_COMBAT, 50);
    set_skill(SS_DEFENSE,      50);

    remove_prop(NPC_M_NO_ACCEPT_GIVE);

    set_stuffed(500);
    set_alignment(-500);

    set_attack_unarmed(0, 20, 30, W_IMPALE, 30, "jaws");
    set_attack_unarmed(1, 15, 20, W_SLASH,  30, "right paw");
    set_attack_unarmed(2, 15, 20, W_SLASH,  30, "left paw");
    set_attack_unarmed(3, 10, 10, W_SLASH,  10, "hind legs");

    refresh_living();
}

public void
init_living()
{
    if(!IS_MEMBER(this_player()) && !this_player()->query_wiz_level())
	return;

    ::init_living();

    add_action("do_emote5","wolfpet"   );
    add_action("do_emote2","wolfhowl"  );
    add_action("do_emote1","wolfsnarl" );
    add_action("do_emote3","wolfdrool" );
    add_action("do_emote4","wolfcircle");
    add_action(  "do_help","wolfhelp"  );
}

public int
do_help()
{
    write("-----------------------------------\n");
    write("| The wolf will allow you to take |\n");
    write("| no fatigue while moving around. |\n");
    write("| However it won't help you in    |\n");
    write("| combat.                         |\n");
    write("| Some emotes:                    |\n");
    write("| wolfpet                         |\n");
    write("| wolfsnarl                       |\n");
    write("| wolfhowl                        |\n");
    write("| wolfdrool                       |\n");
    write("| wolfcircle                      |\n");
    write("-----------------------------------\n");
    return 1;
}

public int
do_emote5()
{
    tell_room(E(TP),QCTNAME(TP)+" pets "+HIS(TP)+" "+short_old()+".\n",TP);
    write("You pet your "+ short_old()+".\n");
    tell_room(E(TP),"The "+ short_old()+" barks happily.\n");
    return 1;
}

public int
do_emote1()
{
    tell_room(E(TP),"The "+short_old()+" mounted by "+QTNAME(TP)+
      " snarls at you.\n",TP);
    write("Your "+short_old()+" snarls at everyone.\n");
    return 1;
}

public int
do_emote2()
{
    tell_room(E(TP),"The "+short_old()+" howls at the moon.\n");
    return 1;
}

public int
do_emote3()
{
    tell_room(E(TP),"The "+short_old()+" mounted by "+QCTNAME(TP)+
      " drools onto the ground, growling softly.\n",TP);
    write("Your "+short_old()+" drools onto the ground, growling "+
      "softly.\n");
    return 1;
}

public int
do_emote4(string str)
{
    int i;
    object *plays;
    object *nosend;
    object target;
    plays = FILTER_LIVE(all_inventory(E(TP)));
    NF("Make the wolf circle whom?\n");
    if(!str)
	return 0;
    for(i=0;i<sizeof(plays);i++)
    {
	if(lower_case(plays[i]->query_name()) == str)
	{
	    target = plays[i];
	    break;
	}
	if(plays[i]->query_race_name() == str)
	{
	    target = plays[i];
	    break;
	}
	if(plays[i]->query_adj()+" "+plays[i]->query_race_name() == str)
	{
	    target = plays[i];
	    break;
	}
    }
    NF("You see no "+str+".\n");
    if(!target)
	return 0;
    nosend = ({target,TP});
    if(target->query_npc)
    {
	TP->catch_msg("You circle "+QTNAME(target)+" with your "+
	  short_old()+" cautiously.\n");
	tell_room(E(TP),QCTNAME(TP)+" circles "+QTNAME(target)+
	  " with "+HIS(TP)+" "+short_old()+" cautiously.\n",nosend);
    }
    else
    {
	TP->catch_msg("You circle "+QCTNAME(target)+" with your "+short_old()+
	  " cautiously.\n");
	tell_room(E(TP),QCTNAME(TP)+" circles "+QCTNAME(target)+" with "+
	  HIS(TP)+" "+short_old()+" cautiously.\n",nosend);
    }
    target->catch_msg(QCTNAME(TP)+" circles you with "+HIS(TP)+
      " "+short_old()+" "+
      "cautiously.\n");
    tell_room(E(TP),"The "+short_old()+" growls softly.\n");
    return 1;
}

void
check_food(int food)
{
    if(food && sizeof(all_inventory()))
	command("emote is all full now.");
    command("drop all");
    alarm = 0;
}

void
enter_inv(object ob, object from)
{
    object hn;

    ::enter_inv(ob, from);

    if(function_exists("create_heap",ob) == FOOD_OBJECT)
    {
	hn = ob->num_heap();

	if (alarm)
	    return;

	set_alarm(1.0,0.0,&command("eat all"));
	set_alarm(3.0,0.0,&check_food(1));
	alarm = 1;
    }
    else if(function_exists("create_heap",ob) == DRINK_OBJECT)
    {
	if (alarm)
	    return;

	hn = ob->num_heap();
	set_alarm(1.0,0.0,&command("drink all"));
	set_alarm(3.0,0.0,&check_food(1));
	alarm = 1;
    }
    else
    {
	if (alarm)
	    return;

	set_alarm(1.0,0.0,&check_food());
	set_alarm(2.0,0.0,&command("emote doesn't want that."));
	alarm = 1;
    }
}
