#pragma no_inherit
#pragma save_binary
#pragma strict_types

inherit "/std/guild/guild_race_sh";

#include "guild.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>
#include <alignment.h>

static private mixed data;

public int
query_guild_tax_race()  
{ 
    int CRIB;
    CRIB=SERVER->query_clan(shadow_who->query_real_name());

    if(CRIB == 0)
    {
        return 1;
    }
    return 3;
}       


public string
query_guild_style_race()               { return GUILD_STYLE; }

public string
query_guild_name_race()         { return GUILD_NAME; }

public string *
query_guild_trainer_race()
{
    string CRIB;
    CRIB=SERVER->query_clan(shadow_who->query_real_name());


    /* If member is a Kinslayer remove their Clan Training room  */
    if (IS_KINSLAYER(shadow_who))
    {
       return ({ (ROOM + "train") });
    }
    

    switch(CRIB)
    {
    case "MacDunn":
        return ({ (ROOM + "train"), (MACDUNN + "macdunn_train")  });
        break;
    case  "Lohrayn":
        return ({ (ROOM + "train"), (LOHRAYN + "lohrayn_train")  });
        break;
    case "MacTabor":
        return ({ (ROOM + "train"), (MACTABOR + "mactabor_train")  });
        break;
    case "MacFadden":
        return ({ (ROOM + "train"), (MACFADDEN + "macfadden_train")  });
        break;
    case "MacVay":
        return ({ (ROOM + "train"), (MACVAY + "macvay_train")  });
        break;
    case "MacFaolain":
        return ({ (ROOM + "train"), (MACFAOLAIN + "macfaolain_train")  });
        break;
    }
    return ({ (ROOM + "train")  });
}


public int
query_guild_family_name()              { return 1; }


public string
query_guild_title_race()
{

    setuid();
    seteuid(getuid());

    if (!sizeof(data))
        return "";

    if (IS_KINSLAYER(shadow_who))
    {
        return data[SNAME] + (data[CNAME] ?
          " Lousy Kinslayer of the Clan " + data[CNAME] : "");
    }

    if (IS_CLANCHIEF(shadow_who))
    {
        return data[SNAME] + (data[CNAME] ?
          " Clan Chief of the Clan " + data[CNAME] : "");
    }

    return data[SNAME] + (data[CNAME] ?
      " of the Clan " + data[CNAME] : "");
}

public int
leave_guild_race()
{
    int tmp;
    object ob;

    shadow_who->catch_tell("You are no longer a member of the " +
      GUILD_NAME + ".\n");

   if (IS_CLANCHIEF(shadow_who))
    {
      if (!SERVER->remove_council_member(SERVER->query_clan(shadow_who->query_real_name())))
      {
        write("An error occured attempting to remove you as " +
              "Clan leader. Please make a bug report.\n");
        return 1;
      }
    }   

    shadow_who->remove_cmdsoul(SOUL);
    shadow_who->update_hooks();
    shadow_who->clear_guild_stat(SS_RACE);
    shadow_who->setup_skill_decay();

    while(ob = present(OBJECT_ID, shadow_who))
        ob->remove_object();

    if (shadow_who->query_default_start_location() == STARTLOC)
        shadow_who->set_default_start_location(shadow_who->query_def_start());

    SERVER->remove_member(shadow_who->query_real_name());

    SCROLLING_LOG(GLOG + "leave",
      capitalize(shadow_who->query_real_name()) +
      " left the " + GUILD_NAME + ". <--");

    return remove_guild_race();
}

private mixed
acceptable_member(object who)
{
    if (((who->query_race() != "human") && (who->query_race() != "dwarf")))
    {
        return "Only humans and dwarves may join the " + GUILD_NAME + "!\n";
    }

    if (who->query_prop() == LIVE_I_UNDEAD)
    {
        return "The " + GUILD_NAME + " appreciates life, not death.\n" +
        "Corpses need not apply.\n";
    }
    return 1;
}

public int
query_guild_keep_player(object ob)
{
    mixed why;

    if (stringp(why = acceptable_member(ob)))
    {
        tell_object(ob, why);
        set_alarm(2.0, 0.0, leave_guild_race);
    }
    return 1;
}


private void
init_guild()
{
    /* This is to prevent server lookups for every 'who' command. */
    data = SERVER->query_member(shadow_who->query_real_name());
    shadow_who->add_cmdsoul(SOUL);
    shadow_who->update_hooks();
}

public void
init_race_shadow(string arg)
{
    setuid();  seteuid(getuid());
    set_alarm(1.0, 0.0, init_guild);
}

public int
add_race_shadow(object who)
{
    return shadow_me(who, "race", GUILD_STYLE, GUILD_NAME);
}

public void
notify_death(object killer)
{
    if (IS_MEMBER(killer))
        SERVER->notify_kinslayer(shadow_who, killer);

    shadow_who->notify_death(killer);
}


/* reset kinslayers starting location */
public void
query_kinslayer_startloc()
{
     if (IS_KINSLAYER(shadow_who))
     {
        if (shadow_who->query_default_start_location() == STARTLOC)
              shadow_who->set_default_start_location(shadow_who->query_def_start());
     }
}