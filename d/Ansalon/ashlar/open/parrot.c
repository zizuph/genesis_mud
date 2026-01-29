/* Ashlar, 26 May 97 - a parrot! */

#include "/d/Ansalon/common/defs.h"

inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/attack";

#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <composite.h>
#include <wa_types.h>

#define PARROTSUBLOC    "_ansalon_parrot_subloc"
#define PARROTNAME      "_ansalon_parrot"

#define A_BEAK 0
#define A_CLAWS 1
#define H_HEAD 0
#define H_BODY 1
#define H_WINGS 2
#define MAXLINES    100
#define DELAY   itof(60 + random(60))

string *colours = ({ "green", "yellow", "blue-green",
    "deep blue", "dark green" });
string *lines = ({ });

void add_line(string l);
varargs void do_random_say(int not_again);

void
create_creature()
{
    string c;	

    set_name("parrot");
    add_name("bird");
    add_name(PARROTNAME);

    set_race_name("parrot");
    c = colours[random(sizeof(colours))];

    set_adj(explode(c," "));

    set_long("The parrot is " + c + ", with carefully preened feathers.\n");

    set_gender(2);
    set_appearance_offset(-25-random(20)); // It's a lovely parrot. :)

    default_config_mobile(3);
    set_skill(SS_DEFENCE,25);
    set_skill(SS_AWARENESS,40);

    add_prop(LIVE_I_NEVERKNOWN,1);
    change_prop(OBJ_M_NO_GET,"@@take_parrot");
    add_prop(CONT_I_WEIGHT, 2000);
    add_prop(CONT_I_HEIGHT, 30);
    add_prop(CONT_I_VOLUME, 1500);

    set_attack_unarmed(A_BEAK,5,10,W_SLASH,40,"sharp beak");
    set_attack_unarmed(A_CLAWS,10,7,W_SLASH,60,"claws");
    set_hitloc_unarmed(H_HEAD,7,20,"head");
    set_hitloc_unarmed(H_BODY,10,55,"body");
    set_hitloc_unarmed(H_WINGS,8,25,"wings");

    trig_new("%s 'says:' %s", "hear_something");
    trig_new("%s 'shouts:' %s", "hear_something");
    trig_new("%s 'nudges you.'", "react_nudge");

#define BASIC_LINES 5
    add_line("Arr!");
    add_line("Where's me grog?");
    add_line("Ohoy, landlubbers!");
    add_line("Where did you hide the gold?");
    add_line("He's drunk again!");

    set_alarm(DELAY,0.0,&do_random_say());
}

mixed
take_parrot()
{
	if (present(PARROTNAME,TP))
    {
    	return "Two parrots rarely get along, so you decide not to " +
            "take another.\n";
    }
    else
        return 0;
}

string *
query_lines()
{
	return lines;
}

void
add_line(string l)
{
    int p;	

	if ((p = member_array(l, lines))==-1)
    {
    	lines += ({ l });
        if (sizeof(lines) > (MAXLINES + BASIC_LINES))
            lines -= ({ lines[BASIC_LINES] });
    }
}

int
hear_something(string speaker, string spoken)
{
    int chance;
    chance = 50 - (strlen(spoken)/4);
    if (chance > 33)
        chance = 33;

    spoken = explode(spoken,"\n")[0];

	if (random(100) < chance)
    {
    	add_line(spoken);
    }
    return 1;
}

varargs void
do_random_say(int not_again)
{
	int i;
    string to_say;

    to_say = lines[random(sizeof(lines))];

    switch(random(3))
    {
    	case 0:
        	to_say = "Waark! " + to_say;
            break;
        case 1:
            to_say = to_say + " Waark!";
            break;
        case 2:
            to_say = "Waark! " + to_say + " Waark!";
    }

    if (E(TO) && E(TO)->query_prop(LIVE_I_IS))
    {
    	tell_room(E(E(TO)),
            "The parrot perched on " + QTNAME(E(TO)) + 
            "'s shoulder says: " + to_say + "\n", E(TO));
        if (interactive(E(TO)))
            E(TO)->catch_msg("The parrot perched on your shoulder " +
                "says: " + to_say + "\n");
    }
    else
    {
    	if (CAN_SEE_IN_ROOM(TO))
    	    TO->command("say " + to_say);
    }
    if (!not_again)
        set_alarm(DELAY,0.0,&do_random_say());
}

void
enter_env(object env, object from)
{
	::enter_env(env, from);

    if(env->query_prop(LIVE_I_IS))
    {
    	env->catch_msg("The " + short() + " climbs up on your shoulder.\n");
        env->add_subloc(PARROTSUBLOC,TO);
        set_alarm(1.0,0.0,&set_no_show_composite(1));
    }

}

void leave_env(object from, object to)
{
    ::leave_env(from,to);
    if(from->query_prop(LIVE_I_IS))
    {
    	from->remove_subloc(PARROTSUBLOC);
        set_no_show_composite(0);
        from->catch_msg("You convince the parrot to leave your shoulder.\n");
    }
}

string
show_subloc(string subloc, object me, object for_obj)
{
    if (subloc != PARROTSUBLOC)
        return "";
    if (me->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
        return "You have a parrot perched on your shoulder.\n";

    if (for_obj == me)
        return "You have a " + short() + " perched upon your shoulder.\n";
    else
        return C(PRONOUN(me)) + " has a " + short() + " perched upon " +
            POSSESSIVE(me) + " shoulder.\n";
}

void
emote_hook(string emote,object actor,string adverb = 0)
{
    if(emote=="nudge")
    {
        set_alarm(3.0,0.0,&do_random_say(1));
    }
}
