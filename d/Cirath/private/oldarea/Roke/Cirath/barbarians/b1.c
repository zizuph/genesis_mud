inherit "/lib/guild_support"; 
inherit "/std/room";

#include "/d/Roke/common/defs.h"
#include "/d/Roke/common/qbits.h"
#include "/sys/ss_types.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/sys/language.h"
#include "/sys/money.h"

#define JM "You hear the sound of a skull breaking as a new barbarian joined the herd.\n"
#define TERA           "/d/Roke/teradeth/"
#define BARBSHADOW     TERA+"barb_shadow"
#define BARBSOUL "/d/Roke/Cirath/barbarians/barb_soul"
#define WUNDERBAUM "/d/Roke/Cirath/barbarians/wunderbaum"
#define BAUMNAME "/d/Roke/Cirath/barbarians/barb_baum"
#define GUILD_NAME     "The Barbarian Herd"
#define GUILD_STYLE    "fighter"
#define GUILD_TYPE     "occupational"
#define BARBLOG     "/d/Roke/Cirath/barbarians/barbarian.log"

joina()
{
  object shadow;
  int result;
  
  seteuid(getuid(TO));

   shadow = clone_object("/d/Roke/Cirath/barbarians/barb_shadow");
  
  if ((result = shadow->shadow_me(this_player(), GUILD_TYPE,
                                  GUILD_STYLE, GUILD_NAME)) != 1)
    {
      /* result = -1 (no name), -2 (wrong type), -3 (no style set),
         -4 (the guild the player already joined don't want this guild.)
         -5 (couldn't shadow the player, security problems. )
         Probably they have set the notify_fail() appropriate.
         0 (already member or player wasn't set properly) */
      
      /* This is one of the few times you destruct is OK to use... */
      shadow->remove_shadow();

      TP->catch_msg("The Elders don't approve you joining this herd. \n"+
                 "Perhaps you're already a member of another occupational\n"+
                 "or layman guild?\n");

      return 1;
    }
  TP->catch_msg("As you declare that you wish to join the herd, a barbarian\n"+
                "arrives and bonks your head with a club...\n\n"+
                "BOOOIINNNG!!\n\n"+
                "He gives you your wunderbaum and then he returns to where \n"+
                "he came from.\n");
  
  say(QCTNAME(TP)+" joined the Mighty Barbarian Herd.\n");
  
  tell_room(TO,JM);
  tell_room("/d/Roke/ikaros/workroom",JM);
  tell_room("/d/Roke/teradeth/workroom",JM);
  
  clone_object(WUNDERBAUM)->move(TP);

  write_file(BARBLOG,TP->query_real_name()+" joined Barbarians "+
           extract(ctime(time()),4,15)+"\n");

  return 1;
}

rejoin()
{
  object shadow;

  if (TP->query_guild_name_occ()!=GUILD_NAME)
    {
      write("But you're not a member. Maybe you should try to join"+
            "instead.\n");
      return 1;
    }

  seteuid(getuid(TO));

  this_player()->remove_guild_occ();

   shadow = clone_object("/d/Roke/Cirath/barbarians/barb_shadow");

  if (shadow->shadow_me(this_player(), GUILD_TYPE,
                        GUILD_STYLE, GUILD_NAME) != 1)
    {
      shadow->remove_shadow();
      TP->catch_msg("Hmm... Something is wrong, please bug report this.\n");
      return 1;
    }

  write_file(BARBLOG,TP->query_real_name()+" rejoined Barbarians "+
           extract(ctime(time()),4,15)+"\n");
  
  write("Your membership has been updated. Have a nice day.\n");
  return 1;
} 
  
  
leava()
{
  int s;
  if (this_player()->remove_guild_occ())
    write("As you leave the Order you feel a mysterious force\n"+
          "that drain you of experience and skills.\n");
  else
    write("There was a strange error, I'm afraid you are\n" +
          "stuck with us.\n");
  
/*  TP->add_exp(-TP->query_exp_combat()/10,1);
*
*  TP->remove_skill(SS_UNARM_COMBAT);
*  TP->remove_skill(SS_ACROBAT);
*  TP->remove_skill(SS_BLIND_COMBAT);
*
*  TP->set_skill(SS_HERBALISM,TP->query_skill(SS_HERBALISM)/2);
* 
*  TP->set_skill(SS_DEFENCE,TP->query_skill(SS_DEFENCE)/2);
*  
*  if (TP->query_skill(SS_WEP_POLEARM)>30)
*    TP->set_skill(SS_WEP_POLEARM,30);
*/  
  present(BAUMNAME,TP)->remove_object();
  TP->remove_cmdsoul(BARBSOUL);
  TP->update_hooks();

  write_file(BARBLOG,TP->query_real_name()+" left Barbarians "+
           extract(ctime(time()),4,15)+"\n");
  
  return 1;
}

create_room()
{ 

    set_short("Barbarians Bonk Tent");
    set_long("You're inside the tent which the barbarians call the 'bonk tent'    \n"+
             "It's here you can join the mighty herd of the Barbarians. The tent  \n"+
             "itself is not very interesting. There's a sign on the wall saying:  \n"+
             "- type 'join herd' if you want to join our mighty herd              \n"+
             "- type 'leave herd' if you want to leave it. Prepare to pay the     \n"+
             "  price.\n"+
             "- type 'update herd' to update your membership.                     \n"+
             "\n"+
             "There is a sign on the wall.\n");


    add_prop(ROOM_I_INSIDE,1);  /* This is a real room */

    add_exit("/d/Roke/teradeth/workroom","teradeth");
    add_exit("/d/Roke/ikaros/workroom","ikaros");
    add_cmd_item("herd","join","@@joina");
    add_cmd_item("herd","leave","@@leava");
    add_cmd_item("herd","rejoin","@@rejoin");

    create_guild_support();

}

init() {
    add_action("gs_meditate", "sleep");
    ::init();
}

leave_inv(object who, object to)
{
  gs_leave_inv(who,to);
  ::leave_inv(who,to);
}

int
gs_hook_already_meditate()
{
  write("You are already sleeping. If you wish to stop sleeping\n"+
        "you can do so by typing 'rise'.\n");
  return 1;
}

void
gs_hook_start_meditate()
{
  write("You lay down on the floor and begin to snore very loudly.    \n"+
        ". As you dream about all your latest kills you feel strangely\n"+
        "relaxed. You find yourself able to <estimate> your differen  \n"+
        "preferences and <set> them at your own desire.               \n"+
        "Just <rise> when you want to wake up.\n");
}

void
gs_hook_rise()
{
  write("You feel very relaxed and rise from the floor and leave the"+
        "floor.\n");
  say(QCTNAME(this_player()) + " wakes up and rises from the floor.\n");
}

int 
gs_hook_catch_error(string str)
{
    write("You can't do that while sleeping.\n");
    return 1;
}
  
