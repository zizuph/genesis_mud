/*
 * /w/aeg/sparkle/npc/pointed_gnome.c
 *
 * The pointed man is a genesis version of the pointed man from the
 * story "The Point!"
 * 
 * Created September 2008, by Aeg (Matthew Morin)
 */
 
#pragma strict_types
#include "../defs.h" 

inherit "/d/Sparkle/area/city/npc/sparkle_npc";
inherit "/d/Genesis/lib/intro"; /* Get him to intro */ 

#include <macros.h>         /* General purpose */
#include <stdproperties.h>  /* References */
#include <ss_types.h>       /* Skills */
#include <wa_types.h>       /* Attack+Hitloc */
#include <cmdparse.h>       /* actions */

/* prototypes */
public void     create_sparkle_npc();
public void     add_point_asks();
public void     point_answer();
public void     north_answer();
public void     south_answer();
public void     east_answer();
public void     west_answer();


/* 
 * Function name:           create_sparkle_npc
 * Description  :           Creates NPC with Sparkle settings
 */
public void
create_sparkle_npc()
{
    set_name("pointed gnome");
    add_name( ({"pointless gnome"}) );
    set_race_name("gnome");
    set_adj( ({"bizarre", "pointing"}) );
    set_gender(G_MALE);
    set_long("This gnome seems to be pointing in every direction.\n");

    /* Stats!    STR, CON, DEX, INT, WIS, DIS */
    set_stats(({ 50,  50,  60,  60,  60,  30 }));
    set_hp(20000); /* Heal it */
    
    /* skills */
    set_skill(SS_DEFENCE,      20);
    set_skill(SS_UNARM_COMBAT, 20);
      
    /* Actions */
    set_act_time(10); /* action every 5 'beats' */
    add_act("emote points up and east.");
    add_act("emote grins and points west and east.");
    add_act("emote smiles and points down and south.");
    add_act("emote frowns, as he points in a general direction.");
    add_act("command point it");
    
    /* Combat Actions */
    set_cact_time(10); /* combat action every 2 'beats' */
    add_cact("shout UtterlyPointless!");
    add_cact("shout YouAreMad!RandomActsOfViolenceArePointless!UtterlyPointless!");
    
    /* asking details */
    set_default_answer(VBFC_ME("default_answer"));
    add_point_asks();
        
} /* create_sparkle_npc */


/*
 * Function name:       add_point_asks
 * Description  :       Gives responses to questions about pointing.
 */
public void
add_point_asks()
{
    add_ask( ({ "point", "pointing" }),
        VBFC_ME("point_answer") );
    add_ask( ({ "north" }),
        VBFC_ME("north_answer") );
    add_ask( ({ "south" }),
        VBFC_ME("south_answer") );
    add_ask( ({ "east" }),
        VBFC_ME("east_answer") );
    add_ask( ({ "west" }),
        VBFC_ME("west_answer") );
        

} /* add_point_asks */


/* 
 * Function name:       default_answer
 * Description  :       give the default response to questions
 */
public string
default_answer()
{
    command("jump randomly");
    command("grumble");
    command("say YouLackAPoint!DoNotBotherMeWithYourPointlessBanter!");
    return "";
    
} /* default_answer */


/*
 * Function name:       swear_word_answer
 * Description  :       response for cursing at NPCs
 */
public string
swear_word_answer()
{
    command("say PointlessVocabulary,You!MakeYourPointAndGetOnWithIt!");
    command("gesture wild");
    command("tap");
    
    return "";
} /* swear_word_answer */


/*
 * Function name:       point_answer
 * Description  :       response to player asking 'job'
 */
public string
point_answer()
{
    command("say My job? It's a good, steady job. Sure is tiring "
            + "though. The gnomes keep me busy at all hours, but the "
            + "pay is good!");
    
    return "";
} /* job_answer */


/* 
 * Function name:       gnome_answer
 * Description  :       give response to asking about gnomes
 */
public string
north_answer()
{
    
    command("say Gnomes? Yeah, they own the place. 'Commercial corporation' "
        + "amongst the bunch of 'em, they say. I donno what it is, or how "
        + "it works, but I know it does.");    
    command("smile brie");
    
    return "";
} /* gnome_answer */


/* 
 * Function name:       building_answer
 * Description  :       give response to asking about building
 */
public string
south_answer()
{
    command("smile joy");
    command("say Beautiful building, isn't it? I just love the architecture "
        + "of this place.");
    command("emote looks toward the high ceiling and says: The gnomes "
        + "wanted this to be the most grand and ornate bank in all the "
        + "world. Artisans from across the donut were hired for their "
        + "assistance in it's construction. It was very expensive.");
        
    return "";
} /* building_answer */


/* 
 * Function name:       bank_answer
 * Description  :       give response to asking about bank
 */
public string
east_answer()
{
    command("say A bank is a place where you can safely store your coins, "
        + "to avoid having to carry them around. The main branch is a "
        + "full service bank, which allows you all the amenities you may "
        + "need for your banking experience.");
    command("smile profes");
    command("say Ask me for a lollipop, if you want one!");
    
    return "";
} /* bank_answer */


/* 
 * Function name:       service_answer
 * Description  :       give response to asking about service
 */
public string
west_answer()
{
    command("emote gestures to the large plaque.");
    command("say You may <deposit>, <withdraw>, check your <account>, "
        + "<minimize> your coins, or <change> your coins.");
    
    return "";
} /* service_answer */