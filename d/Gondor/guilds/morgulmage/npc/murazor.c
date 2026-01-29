#include "/d/Gondor/guilds/morgulmage/morgulmage.h"
#include <const.h>
#include <macros.h>
#include <stdproperties.h>

inherit MORGUL_NPC_DIR + "npc_mage";

void create_mage() 
{
    set_name( "murazor" );
    set_living_name( "murazor" );    
    set_race_name("human");
    set_adj(({ "black-robed", "hunched" }));
    add_name("figure");
    set_short("black-robed hunched figure");
    set_long("Draped in threadworn and faded black robes, this stunted "
        + "figure moves in measured steps, the fingers of its thin, "
        + "grey-spotted hands idly rippling beneath the folds of its "
        + "sleeves like water trickling down needles of hemlock. "
        + "Concealed beneath its hood, the figure's face can barely be "
        + "seen, its expressionless visage covered in shadow.\n");
    set_stats( ({ 150, 150, 150, 200, 200, 200, 0, 200, 0 }), 5);
    set_title("the Heru na Istar, Master of Arcane Studies");

    set_gender(G_NEUTER);
    
    add_prop(NPC_I_NO_LOOKS, 1);
    remove_prop(LIVE_I_NEVERKNOWN);
    
    add_item(({ "face", "visage" }),
        "Almost completely concealed beneath the hood of its faded robe, "
      + "the figure's visage is an unmoving slate of stone, a shadow of "
      + "its former being with only a gleam of red where its eyes once "
      + "where. The hint of a beard can be seen within these shadows, but "
      + "its one vivid colour also faded long ago.\n");

    add_item(({ "hand", "hands", "finger", "fingers" }),
        "Slender fingers extend like slender blades from the thin, "
      + "grey-spotted hands of the hunched figure.\n");    
      
    set_act_time(10);
    add_act("emote idly toys with a thin rusted dirk, the blade twirling "
      + "across its fingers as if lighter than air.");
    
    add_act("emote sifts through a pouch of fine black powder at its "
      + "belt, its lithe fingers snaking through the substance.");
      
    add_act("emote bows its head murmuring in reverie, the tip of "
      + "its beard just penetrating the shadow of its hood.");
      
    add_act("emote rasps quietly: In another age the darkness... the "
      + "flamess...His glory...");
      
    add_ask(({ "age", "past", "history" }),
        "emote rasps wistfully: Our footsteps were the cracks of "
      + "thunder, our gaze incendiary, and all who looked upon us "
      + "trembled in fear at the darkness to come.", 1);
      
    add_ask(({ "darkness" }),
       "emote rasps prophetically: As it was in the beginning "
     + "darkness shall cover all... when the One Ring is found.", 1);
     
    add_cmdsoul(MORGUL_COMMAND_SOUL);
}

public int query_morgul_level()
{
    return ARCHMAGE_LEVEL;
}

public string query_presentation()
{
    return "Murazor " + query_title() + ", legend";
}

public void respond_introduced(string name)
{
    object player = find_living(name);
    if (environment(player) != environment(this_object())) return;
    
    if (!CAN_SEE(this_object(), player)) {
        command("rasp Who's there?");
        return;
    }
    
    command("introduce me to " + OB_NAME(player));
    command("rasp to " + OB_NAME(player) + " Greetings, "
      + (player->query_nazgul() ? "Lord " : "")
      + player->query_mage_name() + ". Here to study, are you?");
}

public void
add_introduced(string name)
{
    set_alarm(2.0, 0.0, &respond_introduced(name));
}

public void respond_hail(object player)
{
    if (environment(player) != environment(this_object())) return;
    
    if (!CAN_SEE(this_object(), player)) {
        command("rasp Who's there?");
        return;
    }
    
    command("mhail " + OB_NAME(player));
}

public void hook_morgul_hail(object hailer) 
{
    set_alarm(2.0, 0.0, &respond_hail(hailer));
}