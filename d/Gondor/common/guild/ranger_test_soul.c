/*
 * /d/Gondor/common/guild/ranger_soul.c
 *
 * The soul of the Gondorian Rangers.
 *
 * Originally coded by Lord Elessar Telcontar
 *
 * Revision history:
 *
 * /Olorin, updates, enhancements and new commands
 * /Mercade, updates and enhancements
 * /Mercade, 17 November 1993, complete revision of the brawl command.
 * /Mercade, 13 April 1994, new command added: mark
 * /Elessar, 15 May 1994, new emotes added: rhush, rpatience
 * /Elessar, 22 Nov 1994, new emote added: rtear
 * /Elessar, 14 Dec 1994, added Mayhem's obscure and confuse trail.
 * /Elessar, 20 Dec 1994, added Mayhem's forage - the hunting skill.
 * /Elessar, 12 Jan 1995, added emote: rpray to <valar>
 * /Elessar, 22 Jan 1996, added about 25 new emotes.
 * Olorin, 19 Aug 1997: New version of brawl.
 * /Elessar, 27 Feb 1998, added commendation.
 * /Stern, March 2000, added rstone, rsit, rtrack, rbrush and extended rpray
 / Skippern, May 2000, added rrecall emote.
 */
#pragma save_binary
#pragma strict_types

inherit "/cmd/std/command_driver.c";
inherit "/d/Gondor/common/lib/binbit.c";

#include <cmdparse.h>
#include <composite.h>
#include <files.h>
#include <formulas.h>
#include <macros.h>
#include <ss_types.h>
#include <std.h>
#include <stdproperties.h>
#include <tasks.h>
#include <wa_types.h>

#include "/d/Gondor/defs.h"

// Must be included before other guild header files:
#include "/d/Gondor/common/guild/lib/punish_defs.h"

// Must be defined before guild header files are included:
#define SOULDESC(x) (this_player()->add_prop(LIVE_S_SOULEXTRA, x))

#include "/d/Gondor/common/guild/lib/brawl_lib.c"
#include "/d/Gondor/common/guild/lib/rwiz.h"
#include "/d/Gondor/common/guild/lib/listen.h"
#include "/d/Gondor/common/guild/lib/campfire.c"
#include "/d/Gondor/common/guild/lib/consider.h"
#include "/d/Gondor/common/guild/lib/diagnose.c"
#include "/d/Gondor/common/guild/lib/mark.h"
#include "/d/Gondor/common/guild/lib/rcomm.h"
#include "/d/Gondor/common/guild/lib/rsongs.h"
#include "/d/Gondor/common/guild/lib/rbattle.h"
#include "/d/Gondor/common/guild/lib/obscure.h"
#include "/d/Gondor/common/guild/lib/special_track.h"
#include "/d/Gondor/common/guild/lib/forage.c"
#include "/d/Gondor/common/guild/lib/emotes.h"
#include "/d/Gondor/common/guild/lib/stealth.h"

/*
 * Return a name in order to get a nice printout.
 */
string
get_soul_id()
{
    return "rangers";
}

/*
 * Identify this soul as a command soul.
 */
int
query_cmd_soul()
{
    return 1;
}

/*
 * Returns a mapping of the form "verb":"function" with all the commands the
 * player can perform. Please add new commands in aphabetical order.
 */
mapping
query_cmdlist()
{
    setuid();
    seteuid(getuid());
    return ([
             "assign"      : "assign_master",
             "battle"      : "battle",
             "blind"       : "blind",
             "brawl"       : "brawl",
             "captain"     : "captain",
             "commend"     : "commend_ranger",
             "company"     : "company",
             "consider"    : "consider",
             "deputy"      : "deputy",
             "diagnose"    : "diagnose",
             "disarm"      : "disarm",
             "forage"      : "try_forage",
             "gather"      : "try_gather",
             "grsay"       : "speak_adunaic",
             "guildlist"   : "guildlist",
             "hail"        : "hail",
             "ghail"       : "hail",
             "kisshand"    : "kisshand",
             "knee"        : "knee",
             "rknee"       : "knee",
             "rhear"       : "do_listen",
             "handkiss"    : "handkiss",
             "help"        : "help",
             "rgleam"      : "rgleam",
             "rhush"       : "hush",
             "mark"        : "mark",
             "newtoken"    : "newtoken",
             "obscure"     : "obscure",
             "ranger"      : "make_ranger",
             "rangertell"  : "rangertell",
             "rangerupdate": "rangerupdate",
             "confuse"     : "confuse",
             "rbow"        : "rbow",
             "rbrush"      : "rbrush",
             "rburp"       : "rburp",
             "rbearing"    : "find_bearing",
             "rcloak"      : "cloak_wrap",
             "runcloak"    : "cloak_unwrap",
             "rcurtsey"    : "rcurtsey",
             "rcheck"      : "rcheck",
             "rcheek"      : "rcheek",
             "rembrace"    : "rembrace",
             "rgrip"       : "rgrip",
             "rgrim"       : "rgrim",
             "rgazefire"   : "gaze_fire",
             "rgaze"       : "emote_cap_gaze",
             "rhome"       : "rhome",
             "rinspect"    : "inspect_weapon",
             "rintro"      : "ranger_intro_type",
             "rconfuse"    : "confuse",
             "rdirt"       : "emote_dirt",
             "rlaugh"      : "emote_laugh",
             "rlist"       : "list_active_rangers",
             "grlist"      : "list_active_rangers",
             "rlisten"     : "rlisten",
             "rmentor"     : "mentor",
             "unmentor"    : "un_mentor",
             "rrelief"     : "rrelief",
             "rdanger"     : "emote_danger",
             "rpick"       : "emote_pick",
             "rpoke"       : "poke_fire",
             "rpray"       : "ranger_pray",
             "rrest"       : "emote_rest",
             "rrecall"     : "rrecall",
             "rrub"        : "rub_token",
             "rsit"        : "rsit",
             "rstone"      : "rstone",
             "rstudy"      : "emote_study",
             "rpatience"   : "rpatience",
             "rtear"       : "rtear",
             "rtitles"     : "rtitles",
             "rtrack"      : "rtrack",
             "rtroubled"   : "emote_troubled",
             "rweary"      : "rweary",
             "rwipe"       : "wipe_weapon",
             "rwait"       : "rwait",
             "rwarm"       : "warm_by_fire",
             "rwarmback"   : "warm_back_by_fire",
             "rpardon"     : "pardon_outlaw",
             "rparley"     : "emote_parley",
             "sing"        : "do_song",
             "stealth"     : "stealth_mode",
             "stop"        : "stop_brawl",
             "trip"        : "trip",
             "suspicious"  : "suspicious",
             "unassign"    : "unassign_master",
             "unranger"    : "unmake_ranger",
             "unrangerp"   : "unmake_ranger",
             "unpunish"    : "unpunish_ranger",
             "notrain"     : "block_ranger",
             "notrade"     : "block_ranger",
             "noaccess"    : "block_ranger",
             "noskills"    : "block_ranger",
             "nospells"    : "block_ranger",
             "noabilities" : "block_ranger",
             "degrade"     : "degrade_ranger",
             "reward"      : "reward_ranger",
             "pupilize"    : "pupilize_ranger",
             "expel"       : "expel_ranger",
             "ban"         : "ban_ranger",
             "unban"       : "unban_player",
             "outlaw"      : "outlaw_enemy"
     ]);
}

/*
 * Below this line come all the functions themselves. Please add new functions
 * in alphabetical order. Service and secondary functions can be added
 * wherever you like.
 */

int
battle(string str)
{
    object  enemy,
           *ob;
    string *cries = BATTLE_CRY,
            rname = QRACE(TP);
    int     n;

    switch (rname)
    {
    case "dwarf":
        cries += BATTLE_CRY_DWARVES;
        break;
    case "elf":
        cries += BATTLE_CRY_ELVES;
        break;
    case "hobbit":
        cries += BATTLE_CRY_HOBBITS;
        break;
    case "human":
        cries += BATTLE_CRY_HUMANS;
        break;
    case "gnome":
        cries += BATTLE_CRY_GNOMES;
        break;
    }
    n = random(sizeof(cries));

    if (!stringp(str))
    {
        if (!objectp(enemy = TP->query_attack()))
        {
            TP->command("shout " + cries[n] + "!");
            return 1;
        }
        else
            ob = ({ enemy });
    }
    else
        ob = parse_this(str, "%l");
    if (!sizeof(ob))
        return 0;
    if(sizeof(ob) > 1)
    {
        TP->catch_msg("Be specific, you cannot kill " + COMPOSITE_LIVE(ob) +
                      " at the same time. \n");
        return 1;
    }
    if (TP->query_attack() == ob[0])
    {
        TP->catch_msg("You shout out: "+cries[n]+"! and attack " +
                      QTNAME(ob[0]) + " with renewed fervour.\n");
        ob[0]->catch_msg(QCTNAME(TP) + " shouts out: "+cries[n] +
                         "! and attacks with renewed fervour.\n");
        say(QCTNAME(TP)+" shouts out: "+cries[n]+"! as " + PRONOUN(TP) +
            " attacks "+QTNAME(ob[0])+" with renewed fervour.\n",
            ({ TP,ob[0] }));
        return 1;
    }
    if (!F_DARE_ATTACK(TP, ob[0]))
    {
        NF("Umm... no, You do not have enough self-discipline to dare!\n");
        return 0;
    }
    TP->catch_msg("You shout out: "+cries[n]+"! as you join battle with " +
        QTNAME(ob[0]) + ".\n");
    ob[0]->catch_msg(QCTNAME(TP) + " shouts out: "+cries[n]+"! as " +
        PRONOUN(TP) + " joins battle with you.\n");
    say(QCTNAME(TP)+" shouts out: "+cries[n]+"! as " + PRONOUN(TP) +
        " joins battle with "+QTNAME(ob[0])+".\n",({ TP,ob[0] }));
    /* 
     * this construct does not allow 'battle second man' if there are
     * several men with the same real_names in the room
       TP->command("kill " + ob[0]->query_real_name());
     */
    TP->command("$kill " + str);
    return 1;
}

int
hail(string str)
{
    object *oblist;
    string *hails = ({"the Free Peoples","Gondor","Ithilien"});
    int     cno;

    if (TP->query_npc())
        cno = TP->query_company_no();
    else
        cno = query_bin_bits(1,16,2,TP);

    if (!strlen(str))
    {
        write("You hail everybody in the name of "+hails[cno]+".\n");
        all(" bows deeply, saying: Hail "+hails[cno]+"!");
        return 1;
    }
    oblist = parse_this(str, "[the] %l");

    if (!sizeof(oblist))
    {
        NFN0("Hail who?");
    }

    actor("You hail", oblist, " in the name of "+hails[cno]+".");
    target(" bows deeply before you, saying: Hail "+hails[cno]+"!", oblist);
    all2act(" bows before", oblist, " saying: Hail "+hails[cno]+"!");
    return 1;
}

int
guildlist(string str)
{
    string name;
    object ob;

    if (strlen(str))
    {
        if (!(TP->query_wiz_level()))
            NFN0("Curious aren't we?");

        if (!(ob = find_player(str)))
            NFN0("No such player found.");

        name = CAP(str) + " is ";
    }
    else
    {
        ob = TP;
        name = "You are ";
    }

    str = ob->list_mayor_guilds();

    if (strlen(str))
        write(name + "member of following guilds.\n" + str);
    else
        write(name + "not member of any guilds.\n");

    return 1;
}

int
handkiss(string str)
{
    object *oblist;

    oblist = parse_this(str, "[the] %l");

    if (!sizeof(oblist))
    {
        NFN0("Offer the hand to whom to kiss?");
    }
    else
    {
        oblist = ({ oblist[0] });
    }

    actor("You offer your hand to", oblist, " to be kissed.");
    target(" raises " + POSSESSIVE(TP) +
        " hand to you, offering it to be kissed.", oblist);
    all2act(" raises " +  POSSESSIVE(TP) + " hand to", oblist,
        " offering it to be kissed.");
    return 1;
}

int
help(string str)
{
    string subject, filename;

    if (!strlen(str))
        return 0;

    setuid();
    seteuid(getuid(TO));

    if (str == "ranger" || str == "guild")
    {
        cat(RANGER_HELP_DIR + "commands");
        return 1;
    }

    if (sscanf(str, "ranger %s", subject) != 1)
        return 0;

    filename = RANGER_HELP_DIR + subject;

    if (file_size(filename) <= 0)
    {
        NFN0("No help on that subject I'm afraid.");
    }

    TI->more(read_file(filename));
    return 1;
}

int
hush(string str)
{
  object *oblist;
  if (!strlen(str))
  {
    write("You whisper 'Hush!', and motion for all to be silent.\n");
    allbb(" whispers 'Hush!', and motions with "+POSSESSIVE(TP)+
      " hand for silence.");
    return 1;
    }
  oblist = parse_this(str,"[at] [the] %l");
  if (!sizeof(oblist))
  {
    write("You whisper 'Hush!' and motion for all to be silent.\n");
    allbb(" whispers 'Hush!', and motions with "+ POSSESSIVE(TP)+
      " hand for you all to be silent.");
    return 1;
    }
  else {
  actor("You whisper 'Hush!', and motion for", oblist, " to be silent.");
  targetbb(" whispers 'Hush!', and motions with "+POSSESSIVE(TP)+
    " hand for you to be silent.",oblist);
  all2actbb(" whispers 'Hush!', and motions with "+POSSESSIVE(TP)+" hand for",
    oblist, " to be silent.");
  return 1;
  }
}

int
rtear()
{
  SOULDESC("wiping away a tear");
  write("Your eyes water up, and a tear flows down your cheek.\n");
  allbb("'s eyes slowly water up, and a solitary tear flows down "+
    POSSESSIVE(TP)+ " cheek.");
  return 1;
}

int
kisshand(string str)
{
    object *oblist;

    oblist = parse_this(str, "[the] [hand] [of] [the] %l");

    if (!sizeof(oblist))
    {
        NFN0("Kiss the hand of whom?");
    }
    else
    {
        oblist = ({ oblist[0] });
    }

    actor("You take", oblist, "'s hand into yours, and gently kiss it.");
     target(" takes your hand into " + POSSESSIVE(TP) + (TP->query_gender() == 1 ? "s" : "") +
        ", and gently kisses it.", oblist);
    all2act(" takes", oblist, "'s hand into " + POSSESSIVE(TP) +
        " own, and gently kisses it.");
    return 1;
}

int
suspicious(string str)
{
    object *oblist;

    SOULDESC("looking suspiciously around");

    if (!strlen(str))
    {
        write("You look suspiciously around.\n");
  allbb(" looks suspiciously around.");
        return 1;
    }

    oblist = parse_this(str, "[at] [the] %l");

    if (!sizeof(oblist))
    {
        write("You look suspiciously at the " + str + ".\n");
  allbb(" looks suspiciously at the " + str + ".");
        return 1;
    }

    actor("You look suspiciously at", oblist);
    targetbb(" looks suspiciously at you.", oblist);
    all2actbb(" looks suspiciously at", oblist);
    return 1;
}

int
rpatience(string str)
{
  object *oblist;
  if (!strlen(str))
    {
      write("You counsel everybody to have patience.\n");
      all(" counsels everyone to be patient.");
      return 1;
    }
  oblist = parse_this(str, "[the] %l");
  if (str == "me" || str == "myself")
    {
      write("You decide to be more patient.\n");
      all(" decides to be more patient.");
      return 1;
    }
  if (!sizeof(oblist))
    {
      write("You counsel everybody to be patient.\n");
      all(" counsels everyone to be patient.");
      return 1;
    }
  actor("You counsel", oblist, " to be patient.");
  target(" counsels you to be patient.",oblist);
  all2act(" counsels",oblist," to be patient.");
  return 1;
}

int
do_prayer(string prayer, mixed *oblist)
{
  mixed *weapons;
  string blade;
  prayer = lower_case(prayer);

  switch(prayer) 
    {
    case "yavanna":
    case "kementari":
        write("You kneel and offer prayer to Yavanna Kementari, asking " +
              "that spring and regrowth will never fail these lands.\n");
        all(" kneels and offers prayer to Yavanna Kementari, asking that " +
            "spring and regrowth will never fail these lands.");
        return 1;
        break;
    case "aule":
    case "mahal":
      
      blade = "blade";  
        
      if (!sizeof(oblist)) 
      {
        weapons = TP->query_weapon(-1);   
        if (sizeof(weapons))
        {
              blade = weapons[0]->short();
        }       
        write("You close your eyes briefly as you pray to Aule Mahal, " +
              "asking that your " + blade  + " will prove as strong and " +
              "steadfast as your heart.\n");
        all(" closes " + POSSESSIVE(TP) + " eyes briefly as " +
           PRONOUN(TP) +  " prays to Aule Mahal, asking that " +
           POSSESSIVE(TP) + " " + blade + " will prove as strong and " +
           "steadfast as " + POSSESSIVE(TP) +  " heart.");
      }
      else {
        actor("You close your eyes briefly as you pray to Aule Mahal, " +
              "asking that", oblist, "'s blade and heart will prove " +
              "equally strong and steadfast.");
        target(" closes "+ POSSESSIVE(TP) + " eyes briefly as " +
               PRONOUN(TP) + " prays to Aule, asking that your blade will " +
               " prove as strong and steadfast as your heart.", oblist);
        all2act(" closes "+ POSSESSIVE(TP) + " eyes briefly as " +
                PRONOUN(TP) + " prays to Aule Mahal, asking that", oblist, 
                "'s blade and heart will prove equally strong and " +
                "steadfast.");
      }
      return 1;
      break;
    case "manwe":
    case "sulimo":
      if (!sizeof(oblist)) {
        write("Turning your face to the West, you offer a prayer to " +
              "Manwe Sulimo the High King of Arda, asking him to rekindle " +
              "your courage.\n");
        all(" turns " + POSSESSIVE(TP) + " face to the West, and offers " +
            "a prayer to Manwe Sulimo the High King of Arda, asking him " +
            "to rekindle " + POSSESSIVE(TP) + " courage.");
      }
      else {
        actor("Turning your face to the West, you offer a prayer to "+
              "Manwe Sulimo the High King of Arda, asking him to rekindle", 
              oblist,"'s courage.");
        target(" turns "+POSSESSIVE(TP)+" face to the West, and offers "+
               "a prayer to Manwe Sulimo the High King of Arda, asking him " +
               "to rekindle your courage.", oblist);
        all2act(" turns "+ POSSESSIVE(TP) + " face to the West, and offers "+
                "a prayer to Manwe Sulimo the High King of Arda, asking " +
                "him to rekindle", oblist, "'s heart.");
      }
      return 1;
      break;
    case "nienna":
      if (!sizeof(oblist)) {
        write("You bend your head and give prayer to Nienna, asking that "+
              "she will strengthen your heart and turn your sorrow to " +
              "wisdom.\n");
        all(" bends " + POSSESSIVE(TP) + " head and gives prayer to " +
            "Nienna, asking that she will turn " + POSSESSIVE(TP) +
            " sorrow into wisdom and strenghten " + POSSESSIVE(TP) +  
            " heart.");
      }
      else {
        actor("You bend your head and give prayer to Nienna, asking that "+
              "she will turn sorrow into wisdom and strenghten", 
              oblist,"'s heart.");
        target(" bends "+POSSESSIVE(TP)+" head and gives prayer to Nienna, "+
               "asking that she will turn your  sorrow to wisdom and " +
               "strengthen your heart.", oblist);
        all2act(" bends "+POSSESSIVE(TP)+" head and gives prayer to Nienna, "+
                "asking that she will turn sorrow to wisdom and strengthen",
                oblist, "'s heart.");
      }
      return 1;
      break;
    case "orome":
    case "araw":
      if (!sizeof(oblist)) {
        write("You stand still and give prayer to Orome Araw, asking for a "+
              "bountiful hunt.\n");
        all(" stands still for a moment praying to Orome Araw, asking for a "+
            "bountiful hunt.");
      }
      else {
        actor("You stand still and give prayer to Orome Araw, asking for a "+
              "bountiful hunt for",oblist,".");
        target(" stands still for a moment, praying for Orome Araw to " +
               "provide you with a bountiful hunt.",oblist);
        all2act(" stands still for a moment praying to Orome Araw, asking " +
                "for a bountiful hunt for",oblist,".");
      }
      return 1;
      break;
    case "ulmo":
      if (!sizeof(oblist)) {
        write("You clasp your hands and give prayer to Ulmo, asking that he "+
              "provide calm waters for the coming sea-voyage.\n");
        all(" clasps "+POSSESSIVE(TP)+" hands praying to Ulmo, asking for "+
            "calm waters for the coming sea-voyage.");
      }
      else {
        actor("You clasp your hands and give prayer to Ulmo, asking that he "+
              "provide calm waters for",oblist,"'s coming sea-voyage.");
        target(" clasps "+POSSESSIVE(TP)+" hands in prayer to Ulmo, asking "+
               "for calm waters for your coming sea-voyage.",oblist);
        all2act(" clasps "+POSSESSIVE(TP)+" hands in prayer to Ulmo, asking "+
                "for calm waters for",oblist,"'s coming sea-voyage.");
      }
      return 1;
      break;
    case "tulkas":
    case "astaldo":
      if (!sizeof(oblist)) {
        write("You kneel and give prayer to Tulkas, asking that he stand "+
              "with you in the coming battle.\n");
        all(" kneels and prays to Tulkas, asking for prowess in the coming "+
            "battle.");
      }
      else {
        actor("You kneel and give prayer to Tulkas, asking that he stand "+
              "with",oblist," in the coming battle.");
        target(" kneels, praying to Tulkas that he stand with you in the "+
               "coming battle.",oblist);
        all2act(" kneels, praying to Tulkas that he stand with",oblist,
                " in the coming battle.");
      }
      return 1;
      break;
    case "elbereth":
    case "varda":
      if (!sizeof(oblist)) {
        write("You raise your hands towards the sky and give prayer to "+
              "Elbereth, asking her to shine a light on the paths of your "+
              "journey.\n");
        all(" raises "+POSSESSIVE(TP)+" hands towards the sky, praying for "+
            "Elbereth to shine a light on the paths of "+POSSESSIVE(TP)+
            " journey.");
      }
      else {
        actor("You raise your hands towards the sky and give prayer to "+
              "Elbereth, asking her to shine a light on the paths of",
              oblist,"'s journey.");
        target(" raises "+POSSESSIVE(TP)+" hands towards the sky, praying "+
               "for Elbereth to shine a light on the paths of your journey.",
               oblist);
        all2act(" raises "+POSSESSIVE(TP)+" hands towards the sky, praying "+
                "for Elbereth to shine a light on the paths of",oblist,
                "'s journey.");
      }
      return 1;
      break;
    default:
      write("You stop and pray in reverence of Eru Illuvatar and all the "+
            "Valar who created the world.\n");
      all(" prays in reverence of Eru Illuvatar and all the Valar who "+
          "created the world.");
      return 1;
      break;
    }  
}

int
ranger_pray(string str)
{
    string prayer;
    mixed *pl;
    if (strlen(str))
    {
        if (!parse_command(str, ({}), "'to' %w", prayer) &&
            (!parse_command(LOW(str), all_inventory(ENV(TP)),
                "'to' %w 'for' %l", prayer, pl) ||
             !sizeof(pl = NORMAL_ACCESS(pl, 0, 0))))
        {
            NF0("Rpray to which Valar (for whom)?\n");
        }
    }
    if (sizeof(pl) && pl[0] == TP)
        pl = ({ });
    return do_prayer(prayer, pl);
}
