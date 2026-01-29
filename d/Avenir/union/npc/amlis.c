/*
 * - /d/Avenir/union/npc/amlis.c
 *
 * Npc emote trainer for the Union
 *
 * Revisions:
 * 	Lucius, Jul 2017: Re-Code.
 *
 */
#pragma strict_types
#include "../defs.h"

inherit (NPC + "npc");

#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <stdproperties.h>

// For testing emotes.
#undef TEST

private static int flag;
private static object embraced;


private void
arm_me(void)
{
    object ob = clone_object("/std/weapon");
    ob->set_wt(W_SWORD);
    ob->set_dt(W_IMPALE);
    ob->set_name("rapier");
    ob->set_short("shadow rapier");
    ob->move(TO, 1);
    command("$wield rapier");

    ob = clone_object("/std/weapon");
    ob->set_wt(W_KNIFE);
    ob->set_dt(W_IMPALE);
    ob->set_name("dirk");
    ob->set_short("shadow dirk");
    ob->move(TO, 1);
    command("$wield dirk");
}

public void
create_monster(void)
{
    set_name("amlis");
    set_race_name("shadow");
    set_short("insubstantial shadow");
    set_long("This shadow is seemingly more solid than the rest, "+
	"by its stature and presence, it seems to be the shadow of "+
	"a Warrior.\n");

    add_prop(NPC_I_NO_LOOKS, 1);
    add_prop(LIVE_I_NO_BODY, 1);
    add_prop(OBJ_M_NO_MAGIC, 1);
    add_prop(OBJ_M_NO_ATTACK, 1);
    add_prop(LIVE_I_NO_CORPSE, 1);
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(NPC_M_NO_ACCEPT_GIVE, 1);
    add_prop(OBJ_M_NO_MAGIC_ATTACK, 1);
    add_prop(LIVE_I_NO_GENDER_DESC, 1);
   
    set_no_show_composite(1);
    set_stats(({ 100, 100, 100, 100, 100, 100 }));

    make_member();

    arm_me();
    equip(({OBJ + "band_e", OBJ + "cape", OBJ + "boots",
	    OBJ + "shirt", OBJ + "pants" }));
}

public object
query_embraced(void)
{
    return embraced;
}

public void
set_embraced(object who, int second)
{
    string which, *souls;

    if (!objectp(who) || !present(who, environment()))
    {
	remove_object();
	return;
    }

    embraced = who;
    souls = regexp(who->query_cmdsoul_list(), "union");

    foreach(string one : souls)
    {
	/* Only add souls from the "spheres" directory. */
	which = implode(explode(one, "/")[-2..-2], "");

	if (which != "union")
	    add_cmdsoul(one);
    }

    update_hooks();

    set_gender(who->query_gender());
    set_alignment(who->query_alignment());
    set_base_stat(SS_OCCUP, who->query_base_state(SS_OCCUP));
    TO->set_union_sphere(who->query_union_sphere());

    if (second)
    {
	flag = second;
	set_short("simulacrum");
	set_name("__simulacra");
	remove_name("shadow");
	return;
    }

    who->catch_tell("The shadow seems to meld with you and you feel a "+
	"tingling sensation pass through your body before the shadow "+
	"once more draws away, appearing a bit more solid than it had.\n");
    tell_room(environment(who), "The shadow seems to consume "+ QTNAME(who) +
	", but it quickly draws away again, seemingly more solid than "+
	"it was previously.\n", ({ TO, who }));
}

public void init_living()		{ }
public void add_introduced(string str)	{ }
public int catch_question(string str)	{ }

/*
 * Function name: emote_hook
 * Description  : Whenever an emotion is performed on this living, or when it
 *                is performed on in the room in general, this function is
 *                called to let the living know about the emotion. This way we
 *                can avoid the usage of all those costly triggers.
 * Arguments    : string emote - the name of the emotion performed. This
 *                    always is the command the player typed, query_verb().
 *                object actor - the actor of the emotion.
 *                string adverbs - the adverb used with the emotion, if there
 *                    was one. When an adverb is possible with the emotion,
 *                    this argument is either "" or it will contain the used
 *                    emotion, preceded by a " " (space). This way you can
 *                    use the adverb in your reaction if you please without
 *                    having to parse it further.
 *                object *oblist - the targets of the emotion, if any.
 *                int cmd_attr - the command attributes, if any.
 *                int target - if true, this object was a target of the emote.
 */
private string *no_emote = ({
    "ask", "ectios",
});

public void
emote_hook(string emote, object actor, string adverb, object *oblist,
           int cmd_attr, int target)
{
    float rnd = itof(random(2) + 1);

    if (IN_ARRAY(emote, no_emote)) {
#ifdef TEST
	if (!flag) write("NO_EMOTE\n");
#endif
	return;
    }

    if (flag)
	return;

#ifdef TEST
    write("**emote_hook()\n"+
	"EMOTE: "+ emote +"\nACTOR: "+ actor->query_real_name() + "\n"+
	"ADVERB: "+ adverb +"\nTARGET: "+ (target ? "true\n" : "false\n") +
	"OBLIST: "+ COMPOSITE_WORDS(map(oblist, &->query_real_name())) + "\n");
#endif

    if (strlen(adverb) && (adverb[0] != ' '))
	adverb = " "+ adverb;

#ifdef TEST
    write("HOOK: "+ emote + adverb + " "+
	(target ? OB_NAME(actor) : "") + "\n");
#endif

    set_alarm(rnd, 0.0,
	&command(emote + adverb + " "+ (target ? OB_NAME(actor) : "")));

    if (target)
    {
	set_alarm((rnd + 1.0), 0.0,
	    &command(emote + adverb + " __simulacra"));
    }
}

/*
 * Function name: emote_hook_onlooker
 * Description  : Whenever this living sees an emotion being performed on
 *                someone else, this function is called to let the living know
 *                about the emotion. This way we can avoid the usage of all
 *                those costly triggers.
 * Arguments    : string emote - the name of the emotion performed. This
 *                    always is the command the player typed, query_verb().
 *                object actor - the actor of the emotion.
 *                string adverbs - the adverb used with the emotion, if there
 *                    was one. When an adverb is possible with the emotion,
 *                    this argument is either "" or it will contain the used
 *                    emotion, preceded by a " " (space). This way you can
 *                    use the adverb in your reaction if you please without
 *                    having to parse it further.
 *                object *oblist - the targets of the emotion.
 *                int cmd_attr - the command attributes.
 */
public void
emote_hook_onlooker(string emote, object actor, string adverb,
                    object *oblist, int cmd_attr)
{
    float rnd = itof(random(2) + 1);

    if (IN_ARRAY(emote, no_emote)) {
#ifdef TEST
	if (!flag) write("NO_EMOTE\n");
#endif
	return;
    }

    if (flag)
	return;

#ifdef TEST
    write("** emote_hook_onlooker()\n"+
	"EMOTE: "+ emote +"\nACTOR: "+ actor->query_real_name() + "\n"+
	"ADVERB: "+ adverb +"\nOBLIST: "+
	COMPOSITE_WORDS(map(oblist, &->query_real_name())) + "\n");
#endif

    if (strlen(adverb) && (adverb[0] != ' '))
	adverb = " "+ adverb;

#ifdef TEST
    write("HOOK: "+ emote + adverb + " ...\n");
#endif

    set_alarm(rnd, 0.0,
	&command(emote + adverb +" "+
	    implode(map(oblist, &->query_real_name()), ",")));
}

/*
 * Function name: emote_hook_actor
 * Description  : Whenever a living performs an emote on others, this hook is
 *                called. This way we can avoid the usage of all those costly
 *                triggers.
 * Arguments    : string emote - the name of the emotion performed. This
 *                    always is the command the player typed, query_verb().
 *                object *oblist - the targets of the emotion.
 */
public void
emote_hook_actor(string emote, object *oblist)
{
}

/*
 * Mask these from regular union npc's to avoid problems.
 */
public void
summon_for_union_ceremony(object where)
{
    /* Do nothing */
}

public void
respect(object who)
{
    /* Do nothing */
}

public void
return_ectios(object who)
{
    /* Do nothing */
}

public void
union_hook_got_ectios(object who)
{
    /* Do nothing */
}
