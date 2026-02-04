/*
 * setter.c  (v1.2)
 * A skill setter for wizards.
 * This file is donated to Genesis under standard
 * copyright. May be included in standard distribution.
 * Written by Trenix@Genesis, 8-11-93
 *
 */

inherit "/std/object";

#include <stdproperties.h>    /* Basic object properties               */
#include <ss_types.h>         /* This will include ss_types2.h as well */

#define SYNTAX "You may use one of the following:\n"+ \
               "o  setskill <skill> <level>\n"+ \
               "o  setskill all <level>\n"+ \
               "o  wipeskill <skill>\n"+ \
               "o  wipeskill all\n\n"+ \
               "Examples: setskill sword 50\n"+ \
               "          setskill all 45\n"+ \
               "          wipeskill sword\n"+ \
               "          wipeskill all\n"

/* We know how helpful examples are, and we don't want to go misleading  */
/* people; however, at this point they should be intelligent enough to   */
/* figure it out. After all, they could page the source code.            */

#define FAIL "Foolish mortal, only wizards may use the skill setter.\n"+ \
             "The skill setter turns to sand and falls through your fingers.\n"

#define MAXLEVEL 100  /* Maximum level used by the game. */

void set_all_skills(int value);
int  parse_skill(string str, int value);
void set_my_skill(int skill, int value);

create_object()
{
    seteuid(getuid());
    set_name(({ "setter", "skill setter" }));
    set_pname(({ "setters", "skill setters" }));
    set_long("This is a skill setter, use help setter for more info.\n");
    add_prop(OBJ_I_VALUE,0);
    add_prop(OBJ_I_WEIGHT,0);
    add_prop(OBJ_I_VOLUME,0);
    add_prop(OBJ_I_LIGHT,0);
}

init()
{
    add_action("cmd_help","help");
    add_action("cmd_set","setskill");
    add_action("cmd_wipeskill","wipeskill");
}

int cmd_wipeskill(string str)
{
    if ( !this_player() || !interactive(this_player()) )
    {
        return 0;  /* Just thought I'd check. */
    }
    if ( !this_player()->query_wiz_level() )
    {
        notify_fail( FAIL );
        this_object()->remove_object();
        return 0;
    }
    if ( !str || !stringp(str) )
    {
       notify_fail( SYNTAX );
       return 0;
    }
    if ( str == "all" )
    {
        write("Wiping all skills.\n");
        set_all_skills(0);
        return 1;
    }
    if ( parse_skill(str,0) )
    {
        write(capitalize(str)+" skill wiped.\n");
        return 1;
    }
    notify_fail("Skill not found.\n");
    return 0;
}

int cmd_set(string str)
{
    int level, size;
    string skill, *stuff;

    if ( !this_player() || !interactive(this_player()) )
    {
        return 0;  /* Same here. */
    }
    if ( !this_player()->query_wiz_level() )
    {
        notify_fail( FAIL );
        this_object()->remove_object();
        return 0;
    }
    if ( !str || !stringp(str) )
    {
       notify_fail( SYNTAX );
       return 0;
    }
    stuff = explode(str," ");
    size = sizeof(stuff);
    size--;  /* Arrays start at zero. */
    sscanf(stuff[size],"%d",level);
    if ( !level || !intp(level) )
    {
        notify_fail( SYNTAX );  /* Use wipeskill instead. */
        return 0;
    }
    stuff = stuff[0..(size-1)];  /* Take the value off the string. */
    skill = implode(stuff," ");  /* Put the string back together.  */
    if ( level > MAXLEVEL )
    {
        write("Warning, the game only uses levels 0 - "+MAXLEVEL+".\n");
    }
    if ( level < 0 )
    {
        notify_fail("Please use a number between 0 and "+MAXLEVEL+".\n");
        return 0;
    }
    if ( skill == "all" )
    {
        write("Setting all skills to level "+level+".\n");
        set_all_skills(level);
        return 1;
    }
    if ( parse_skill(skill,level) )
    {
        write(capitalize(skill)+" set to level "+level+".\n");
        return 1;
    }
    notify_fail("Skill not found.\n");
    return 0;
}

int parse_skill(string str, int level)
{
    switch(str)
    {
        case "sword" :
             set_my_skill(SS_WEP_SWORD,level);
             break;
        case "polearm" :
             set_my_skill(SS_WEP_POLEARM,level);
             break;
        case "axe" :
             set_my_skill(SS_WEP_AXE,level);
             break;
        case "knife" :
             set_my_skill(SS_WEP_KNIFE,level);
             break;
        case "club" :
             set_my_skill(SS_WEP_CLUB,level);
             break;
        case "missles" :
             set_my_skill(SS_WEP_MISSILE,level);
             break;
        case "javelin" :
             set_my_skill(SS_WEP_JAVELIN,level);
             break;
        case "two handed combat" :
             set_my_skill(SS_2H_COMBAT,level);
             break;
        case "unarmed combat" :
             set_my_skill(SS_UNARM_COMBAT,level);
             break;
        case "blind fighting" :
             set_my_skill(SS_BLIND_COMBAT,level);
             break;
        case "blindfighting" :  /* May be used this way as well. */
             set_my_skill(SS_BLIND_COMBAT,level);
             break;
        case "parry" :
             set_my_skill(SS_PARRY,level);
             break;
        case "defense" :
             set_my_skill(SS_DEFENSE,level);
             break;
        case "spellcraft" :
             set_my_skill(SS_SPELLCRAFT,level);
             break;
        case "herbalism" :
             set_my_skill(SS_HERBALISM,level);
             break;
        case "alchemy" :
             set_my_skill(SS_ALCHEMY,level);
             break;
        case "transmutation spells" :
             set_my_skill(SS_FORM_TRANSMUTATION,level);
             break;
        case "illusion spells" :
             set_my_skill(SS_FORM_ILLUSION,level);
             break;
        case "divination spells" :
             set_my_skill(SS_FORM_DIVINATION,level);
             break;
        case "enchantment spells" :
             set_my_skill(SS_FORM_ENCHANTMENT,level);
             break;
        case "conjuration spells" :
             set_my_skill(SS_FORM_CONJURATION,level);
             break;
        case "abjuration spells" :
             set_my_skill(SS_FORM_ABJURATION,level);
             break;
        case "fire spells" :
             set_my_skill(SS_ELEMENT_FIRE,level);
             break;
        case "air spells" :
             set_my_skill(SS_ELEMENT_AIR,level);
             break;
        case "earth spells" :
             set_my_skill(SS_ELEMENT_EARTH,level);
             break;
        case "water spells" :
             set_my_skill(SS_ELEMENT_WATER,level);
             break;
        case "life spells" :
             set_my_skill(SS_ELEMENT_LIFE,level);
             break;
        case "death spells" :
             set_my_skill(SS_ELEMENT_DEATH,level);
             break;
        case "open lock" :
             set_my_skill(SS_OPEN_LOCK,level);
             break;
        case "pick pocket" :
             set_my_skill(SS_PICK_POCKET,level);
             break;
        case "acrobat" :
             set_my_skill(SS_ACROBAT,level);
             break;
        case "find and remove traps" :
             set_my_skill(SS_FR_TRAP,level);
             break;
        case "sneak" :
             set_my_skill(SS_SNEAK,level);
             break;
        case "hide" :
             set_my_skill(SS_HIDE,level);
             break;
        case "backstab" :
             set_my_skill(SS_BACKSTAB,level);
             break;
        case "appraise enemy" :
             set_my_skill(SS_APPR_MON,level);
             break;
        case "appraise object" :
             set_my_skill(SS_APPR_OBJ,level);
             break;
        case "appraise value" :
             set_my_skill(SS_APPR_VAL,level);
             break;
        case "swim" :
             set_my_skill(SS_SWIM,level);
             break;
        case "climb" :
             set_my_skill(SS_CLIMB,level);
             break;
        case "animal handling" :
             set_my_skill(SS_ANI_HANDL,level);
             break;
        case "location sense" :
             set_my_skill(SS_LOC_SENSE,level);
             break;
        case "tracking" :
             set_my_skill(SS_TRACKING,level);
             break;
        case "hunting" :
             set_my_skill(SS_HUNTING,level);
             break;
        case "awareness" :
             set_my_skill(SS_AWARENESS,level);
             break;
        case "trading" :
             set_my_skill(SS_TRADING,level);
             break;
        default :
             return 0;
    }
    return 1;
}

void set_my_skill(int skill, int level)
{
    this_player()->set_skill(skill,level);
}

void set_all_skills(int level)
{
    object player;

    player = this_player();
    player->set_skill(SS_WEP_SWORD,level);
    player->set_skill(SS_WEP_POLEARM,level);
    player->set_skill(SS_WEP_AXE,level);
    player->set_skill(SS_WEP_KNIFE,level);
    player->set_skill(SS_WEP_CLUB,level);
    player->set_skill(SS_WEP_MISSILE,level);
    player->set_skill(SS_WEP_JAVELIN,level);
    player->set_skill(SS_2H_COMBAT,level);
    player->set_skill(SS_UNARM_COMBAT,level);
    player->set_skill(SS_BLIND_COMBAT,level);
    player->set_skill(SS_PARRY,level);
    player->set_skill(SS_DEFENSE,level);
    player->set_skill(SS_SPELLCRAFT,level);
    player->set_skill(SS_HERBALISM,level);
    player->set_skill(SS_ALCHEMY,level);
    player->set_skill(SS_FORM_TRANSMUTATION,level);
    player->set_skill(SS_FORM_ILLUSION,level);
    player->set_skill(SS_FORM_DIVINATION,level);
    player->set_skill(SS_FORM_ENCHANTMENT,level);
    player->set_skill(SS_FORM_CONJURATION,level);
    player->set_skill(SS_FORM_ABJURATION,level);
    player->set_skill(SS_ELEMENT_FIRE,level);
    player->set_skill(SS_ELEMENT_AIR,level);
    player->set_skill(SS_ELEMENT_EARTH,level);
    player->set_skill(SS_ELEMENT_WATER,level);
    player->set_skill(SS_ELEMENT_LIFE,level);
    player->set_skill(SS_ELEMENT_DEATH,level);
    player->set_skill(SS_OPEN_LOCK,level);
    player->set_skill(SS_PICK_POCKET,level);
    player->set_skill(SS_ACROBAT,level);
    player->set_skill(SS_FR_TRAP,level);
    player->set_skill(SS_SNEAK,level);
    player->set_skill(SS_HIDE,level);
    player->set_skill(SS_BACKSTAB,level);
    player->set_skill(SS_APPR_MON,level);
    player->set_skill(SS_APPR_OBJ,level);
    player->set_skill(SS_APPR_VAL,level);
    player->set_skill(SS_SWIM,level);
    player->set_skill(SS_CLIMB,level);
    player->set_skill(SS_ANI_HANDL,level);
    player->set_skill(SS_LOC_SENSE,level);
    player->set_skill(SS_TRACKING,level);
    player->set_skill(SS_HUNTING,level);
    player->set_skill(SS_LANGUAGE,level);
    player->set_skill(SS_AWARENESS,level);
    player->set_skill(SS_TRADING,level);
}

int cmd_help(string str)
{
    if ( !str || !stringp(str) )
    {
        return 0;
    }
    if ( str != "setter" && str != "skill setter" )
    {
        return 0;  /* The're trying to get help on something else. */
    }
    write(
  "The Skill Setter v1.2 by Trenix@Genesis\n\n"+
   SYNTAX+"\n"+
  "These are the skills you may train in:\n\n"+
  "Attack skills:\n"+
  "sword              polearm            axe                 "+
      "knife\n"+
  "club               missles            javelin             "+
      "two handed combat\n"+
  "unarmed combat     blind fighting\n\n"+
  "Defensive skills:\n"+
  "parry              defense\n\n");
 write("Spells:\n"+
  "spellcraft         herbalism          alchemy             "+
      "transmation spells\n"+
  "illusion spells    divination spells  enchantment spells  "+
      "conjuration spells\n"+
  "abjuration spells  fire spells        air spells          earth spells\n"+
  "water spells       life spells        death spells\n\n"+
  "Thief skills:\n"+
  "open lock          pick pocket        find and remove traps\n"+
  "sneak              hide               backstab\n\n");
 write("General skills:\n"+
  "acrobat            appraise enemy     appraise object     appraise value\n"+
  "swim               climb              animal handling     location sense\n"+
  "tracking           hunting            awareness           trading\n");
    return 1;
}

/* EOF */
