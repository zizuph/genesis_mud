inherit "/lib/guild_support";
inherit "/std/room";
#include "/d/Roke/defs.h"
#include "/d/Roke/common/defs.h"
#include "/d/Roke/Cirath/defs.h"
#include "/sys/stdproperties.h"
#include <ss_types.h>
#include "/d/Roke/common/qbits.h"
#include "/sys/macros.h"
#include "/d/Roke/Cirath/barbarians/skills.h"

#define JM "You hear the sound of a skull breaking as a new barbarian joined the herd.\n"
#define LM "You hear the sound of brain substance staining the walls of the bonk tent.\n"
#define BARBAR         "/d/Roke/Cirath/Barbarians/"
#define BARBSHADOW     BARBARIANS+"barb_shadow"
#define BARB_SOUL      BARBARIANS+"barb_soul"
#define WUNDERBAUM     BARBARIANS+"bracelet"
#define BAUMNAME       BARBARIANS+"barb_bracelet"
#define GUILD_NAME     "The Barbarian Herd"
#define GUILD_STYLE    "fighter"
#define GUILD_TYPE     "occupational"
#define GUILD_SHADOW   BARBARIANS+"barb_shadow"
#define BARBLOG        CIRATH_LOG

void
create_room()
{

  set_short("Bonk tent");
  set_long("You are standing inside a tent in the barbarian\n"+
           "camp. This tent is called the 'bonk' tent. It's\n"+
           "here, new barbarians start their days in the herd.\n"+
           "The tent itself is quite boring. No furniture and\n"+
           "no decorations on the walls except a little sign.\n"+
           "It reads:\n"+
           "- follow crom, to join the mighty herd of barbarians.\n"+
           "- convert to whimp, to leave the mighty herd\n"+
           "- update membership, to update your membership.\n"+
           "- list guilds, to list your guilds\n");

  INSIDE;

  add_exit(BARBARIANS+"br5", "west");

}

void
init()
{
    ::init();
    add_action("join", "follow");
    add_action("my_leave", "convert");
    add_action("list", "list");
    add_action("update","update");

}


join(str)
{
  object shadow;
  int i;
  object *souls;

  if(str == "crom")
  {

    if (TP->query_race_name() == "elf")
    {
      write("Ha! A puny elf like you wanna join the MIGHTY herd of "+
            "barbarians. NO WAY!\n");
      return 1;
    }

    if (TP->query_race_name() == "hobbit")
    {
      write("What? A little halfling want to join us, be realistic!\n");
      return 1;
    }


    if (TP->query_race_name() == "gnome")
    {
      write("No gnomes will enter this herd. Never!\n");
      return 1;
    }

    if (TP->query_guild_member(GUILD_TYPE))
    {
      write("You can't be a member of two occupational guilds!\n");
      return 1;
    }

    if (TP->query_guild_member("layman") && TP->query_guild_style("fighter"))
    {
      write("Barbarians don't accept fighter layman guilds.\n");
      return 1;
    }

    if (TP->query_guild_member("layman") && TP->query_guild_style("mage"))
    {
      write("Barbarians don't accept mage layman guilds.\n");
      return 1;
    }

    if (TP->query_guild_member("layman") && TP->query_guild_style("cleric"))
    {
      write("Barbarians don't accept cleric layman guilds.\n");
      return 1;
    }

    if (TP->query_alignment()<-550)
    {
      write("You're too evil! Crom doesn't like evil beings!\n");
      return 1;
    }

    if (TP->query_alignment()>550)
    {
      write("Sorry, you are too holy. Try the monks instead, we don't "+
                  "want holy types in our herd.\n");
      return 0;
    }

/*    if (TP->query_exp_combat()/TP->query_exp < 2/3)
*    {
*      notify_fail("Do you really think we would like a whimpy snort like you "+
*                  "in our herd.\n");
*      return 1;
*    }
*/
    shadow = clone_object(GUILD_SHADOW);
    notify_fail("How odd. For some reason you cannot join us.\n");
    if (shadow->shadow_me(TP, GUILD_TYPE, GUILD_STYLE,
                          GUILD_NAME)!=1)
    {
      shadow->remove_object();
      return 0;
    }
    write(break_string(
          "A huge barbarian guard walk up behind you a bonks you in the head "+
          "with his HUGE fist.\n",60));
    write("\nBONK!!!!!\n\n");

    call_out("wake_up",4);

    TP->add_cmdsoul(BARB_SOUL); 

    seteuid(getuid(TO));
    souls = TP->query_cmdsoul_list();
    for (i = 0; i < sizeof(souls); i++)
      TP->remove_cmdsoul(souls[i]);
      TP->add_cmdsoul(BARB_SOUL);
      for (i = 0; i < sizeof(souls); i++)
        if (souls[i] != BARB_SOUL)
          TP->add_cmdsoul(souls[i]);

    clone_object(WUNDERBAUM)->move(TP);

    TP->update_hooks();

    return 1;
  }
  return 0;
}

my_leave(str)
{
  object insignia;
  int result,i;
  object sould;
    


  if (str!="to whimp")
  {
    write("Convvert to what?\n");
    return 1;
  }
    
  if (this_player()->query_guild_name_occ()!=GUILD_NAME)
  {
    notify_fail("You can't leave a guild you are not a member of.\n");
    return 0;
  }
  if (TP->remove_guild_occ())
  {
    write("Suddenly a many ex friends of your runs into the tent and "+
          "starts hitting you. Everything turns black and when you wake "+
          "up, you feel empty in some way.\n");

    for (i = 0; i < 200; i++)
    {
      TP->remove_skill(i);
    }
    
    TP->remove_skill(BARB_SCORE);
    TP->remove_skill(SLAYING);
    TP->remove_skill(BONKING);
    TP->remove_skill(CHOPPING);
    TP->remove_skill(BLOCKING);
    TP->remove_skill(HOLDING);
    TP->remove_skill(STABBING);


    present(BAUMNAME,TP)->remove_object();
    TP->remove_cmdsoul(BARB_SOUL);
    TP->update_hooks();
    write_file(BARBLOG,TP->query_real_name()+" left Barbarians "+
               extract(ctime(time()),4,15)+"\n");
    tell_room(TO,LM);
    tell_room("/d/Roke/valeria/workroom",LM);
    tell_room("/d/Roke/conan/workroom",LM);
  }
  else
    write("Because of an error, you remain with us.\n");
  return 1;
}

int
list()
{
    
  string str;

  str = this_player()->list_major_guilds();
  if (str)
    write("You are a member of the following guilds.\n" + str);
  else
    write("You are not a member of any important guilds.\n");
    
  return 1;
}

void
soul(object ob)
{
    object spells;
    int i;
    string *souls;

    seteuid(getuid(TO));
    souls = ob->query_cmdsoul_list();
    for (i = 0; i < sizeof(souls); i++)
        ob->remove_cmdsoul(souls[i]);
    ob->add_cmdsoul(BARB_SOUL);
    for (i = 0; i < sizeof(souls); i++)
        if (souls[i] != BARB_SOUL)
            ob->add_cmdsoul(souls[i]);
    ob->update_hooks();
}

int 
update(string str)
{
    object shadow;

    if (!str || str != "membership")
    {
        notify_fail("Update what?\n");
        return 0;
    }

    if (TP->query_guild_name_race()!=GUILD_NAME)
    {
        write("Updating shadow.\n");
        shadow = clone_object(GUILD_SHADOW);
        if (shadow->shadow_me(TP, GUILD_TYPE, GUILD_STYLE,
                              GUILD_NAME)!=1)
        {
            write("Couldn't update your shadow. Please contact a wizard about this.+n");
            shadow->remove_object();
        }
    }
    
    write("Done!\n");
    return 1;
}

int
wake_up()
{
  write(break_string(
        "You feel very dizzy as you open your "+
        "eyes again, not knowing how long time has past since the brutal "+
        "attack. Somehow you feel stronger and braver put also more stupid. "+
        "Suddenly you realizes that you're a member of the mighty herd. "+
        "Your dreams have come true.\n",60));
  say(QCTNAME(TP)+" joined the Mighty Barbarian Herd.\n\n");
  
  tell_room(TO,JM);
  tell_room("/d/Roke/valeria/workroom",JM);
  tell_room("/d/Roke/conan/workroom",JM);
  
  write_file(BARBLOG,TP->query_real_name()+" joined Barbarians "+
             extract(ctime(time()),4,15)+"\n");

  return 1;
}