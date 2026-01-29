/*
 * traveller.c
 *
 * Traveller immortal - spreads rumours and legends across Khalakhor.
 * 
 * Khail - February 8, 2002
 */
#pragma strict_type

#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include "/d/Khalakhor/sys/defs.h"
#include "/d/Khalakhor/sys/paths.h"

inherit STDHUMAN;

object my_staff;
int tale_alarm_id,
    has_armed;

/*
 * Function name: arm_me
 * Description  : Clones in the Traveller's staff
 *                and has him wield it.
 *                Transports staff from wherever it is
 *                if the Traveller doesn't actually have
 *                it.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
arm_me()
{
    int return_val;

    seteuid(getuid());

   /* If no staff exists, clone one into the Traveller's */
   /* inventory */
    if (!my_staff)
    {
        my_staff = clone_object("/d/Khalakhor/immortals/traveller/staff");
        my_staff->move(TO,1);
    }
    else if (!present(my_staff, TO))
    {
        command("emote suddenly looks at his empty hands and " +
            "turns around in an awkward circle looking at the " +
            "ground.");
        command("say Drat, where did that staff wander off " +
            "to this time?");
        return_val = my_staff->weapon_recalled(TO);
        if (return_val = 1)
        {
            my_staff = clone_object("/d/Khalakhor/immortals/traveller/staff");
            my_staff->move(TO,1);
        }    
        tell_room(environment(TO), "You smell a strange, metallic odor " +
            "a split second before the air begins to crackle and " +
            "sizzle.  A vertical slash of blue-green lightning rends open " +
            "the air before " + QTNAME(TO) + ", who calmly reaches out " +
            "to apparently grasp the bolt of raw power.  As his hand " +
            "closes around the sinuous energy, it's brilliant glow " +
            "fades, and coalesces into a simple wooden staff.\n");
        command("smile");
        command("say Ahh, there you are!");
    }
    command("wield all");
    my_staff->remove_prop(OBJ_I_LIGHT);
    has_armed = 1;
}

/*
 * Function name: create_khalakhor_human
 * Description  : Turns this object into the Traveller.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
create_khalakhor_human()
{
    set_name("traveller");
    add_name("man");
    set_adj("tall");
    add_adj("greying");
    set_long("This old man appears to be walking with one foot " +
        "in the grave.  Slightly stooped with age, his greying hair " +
        "juts out wildly in all directions, like he just came in " +
        "out of a windstorm.  His skin is deeply tanned, evidence of " +
        "a lifetime spent outdoors, but you you notice his hands are " +
        "completely callous-free.  Despite his wizened appearance, you " +
        "note a flicker in his eye betray a hint that there's " +
        "something more to this man.\n");

    add_prop(OBJ_M_NO_ATTACK, "You try to attack " + QTNAME(TO) +
        ", when the world seems to jolt sideways, and you find " +
        "yourself facing the other way.  " + QCTNAME(TO) +
        " doesn't even seem to have noticed your attempt.\n");

    set_skill(SS_AWARENESS, 100);
    set_skill(SS_BLIND_COMBAT, 100);
    set_skill(SS_UNARM_COMBAT, 100);
    set_skill(SS_DEFENCE, 100);
    set_skill(SS_WEP_POLEARM, 100);

    default_config_npc(300);
    set_alignment(400);
    set_exp_factor(50);
    set_size_descs("tall", "thin");

    add_ask("banshee","@@asked_about_banshee",1);

}

public void
reset_khalakhor_human()
{
    set_alarm(0.5, 0.0, arm_me);
}

public void
orate_tale(string tale, int count, object ob_audience)
{
    string audience,
           audience_pro;

   /* Make sure the traveller can still see in the
    * room */
    if (!CAN_SEE_IN_ROOM(TO))
    {
        command("emote gasp");
        command("say Who turned out the lights?  I can't " +
            "tell a story when I can't see my audience!  " +
            "It spoils the whole thing.");
        return;
    }

   /* Make sure the traveller's audience hasn't logged
    * out, been killed or just wandered off. */
    if (!ob_audience)
    {
        audience = "my_audience";
        audience_pro = "they";
    }
    if (!present(ob_audience, environment(TO)) ||
        !CAN_SEE(TO,ob_audience))
    {
        if (query_remembered(ob_audience->query_real_name()))
        {
            audience = ob_audience->query_met_name();
        }
        else
        {
            audience = "that " + ob_audience->query_nonmet_name();
        }
        audience_pro = HE_SHE(ob_audience);
    }
    if (audience)
    {
        command("frown");
        command("say Now where did " + audience + " go?  " +
            "I guess " + audience_pro + " didn't want to " +
            "hear that story after all.");
        command("grumble");
        command("say Young people these days, always in " +
            "a rush.");
        return;
    }

    audience = ob_audience->query_real_name();

   /* Ok, audience is still here, continue with tale. */
    if (tale == "banshee_tale")
    {
        if (count == 0)
        {
            command("say to " + audience + " Ahh, you " +
                "want to know of the Banshee?  Well, " +
                "that is a tale.  It's said she was once " +
                "a queen among a race that walked these " +
                "lands long before any of the younger " +
                "races arrived.  She fell in love with her " +
                "husband, the king's, brother, the crown " +
                "prince.  When the king found out, he " +
                "had both his wife and his brother " +
                "executed on the spot.");
            command("emote shakes his head in disbelief.");
        }
        else if (count == 1)
        {
            command("say to " + audience + " Out of " +
                "spite, the king buried his brother on " +
                "holy ground, and the queen's body was " +
                "dismembered and cast to the wolves. " +
                "with her remains desecrated on " +
                "unsanctified ground, her spirit was " +
                "trapped on this realm.  In this way, " +
                "the king prevented her and the crown " +
                "prince from being reunited in death.");
            command("sigh mournfully");
        }
        else if (count == 2)
        {
            command("say to " + audience + " The " +
                "queen's spirit went insane with grief " +
                "and lonliness over the centuries.  " +
                "Now, she arises on occasion, slaying " +
                "life wherever she finds it.  Some " +
                "believe she's looking for the soul " +
                "of her lover, reincarnated into the " +
                "body of a mortal.");
        }
        else
        {
            command("say to " + audience + " The " +
                "saddest part of it all, the Banshee " +
                "herself isn't even evil, just insane " +
                "with centuries of longing, much like " +
                "a warrior gone berserk with bloodlust " +
                "in battle.");
        }
        if (count >= 3)
            return;
        else
        {
            count += 1;
            tale_alarm_id = set_alarm(3.0, 0.0, 
                &orate_tale("banshee_tale", count, ob_audience));
            return;
        }
    }
} 

public string
asked_about_banshee()
{
    string player;
    object ob_audience;
    object ob_asked = TP;
    string name_asked = TP->query_real_name();

    if (get_alarm(tale_alarm_id))
    {
        ob_audience = get_alarm(tale_alarm_id)[4][2];
        if (ob_audience = ob_asked)
        {
            return "say Calm down, I haven't finished " +
                "this story yet!";
        }
        player = ob_audience->query_real_name();
        if (query_remembered(player))
        {
            player = ob_audience->query_met_name();
        }
        else
        {
            player = "this " +
                ob_audience->query_nonmet_name();
        }
        return "say Hold your horses, I'm already " +
            "telling a story to " + player +
            ", I'll get to you in a minute.";
    }
    else
    {
        tale_alarm_id = set_alarm(0.5, 0.0, 
            &orate_tale("banshee_tale", 0, ob_asked));
        return "eyebrow approvingly " + name_asked;
    }
}