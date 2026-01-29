/* joinroom.c: The gladiator joinroom: Shiva.
 *     Modified by Serpine: 4-26-95.
 */


inherit "/d/Cirath/std/room";
#include "defs.h"

void
create_room()
{
    set_short("a small chamber");
    set_long("You are in a small chamber carved into an underground "+
             "rock formation. It appears to have been done in some "+
             "unnaturel fashion. Light eminates from the cavern walls"+
             "and a tunnel leads to the north.\n");

  INSIDE
  add_item(({"walls", "wall"}), "The walls seem mysterious.\n");

  add_cmd_item("training", "enter", "Are you certain you are willing "+
      "to make such a sacrifice of blood and freedom? Have you spoken "+
      "to the Speaker of the Gladiators, the Overseers, or others of "+
      "their ilk? Are you just plain mad?\n"+
      "Fools rush in: True Champions size up their targets first.\n"+
      "If you are sure however, then <become slave>.\n");

  add_exit(PSION_ROOM+"hallway1.c", "north", 0, 1);
    reset_room();
}

void init()
{
  ::init();
  add_action("concentrate", "concentrate");
  add_action("update", "update");
}

int concentrate(string str)
{
  string file;
  object sh;
  
  NF("Concentrate on what?\n");
  if (str != "mind") return 0;

  NF("You have already mastered your mind.\n");
  if (IS_MEMBER(TP)) return 0;

  NF("Your mind belongs to someone else.\n");
  if (TP->query_guild_member_occ()) return 0;

  NF("Your mind is locked. Only a master can unlock it.\n");
  if (CHECK_PUNISHMENT(BAR, TP->query_real_name())) return 0;

  NF("The true master is missing: Tell a wizard.\n");
  if(!(sh=CO(GUILD_SHADOW))) return 0;

  switch(sh->shadow_me(TP, GUILD_TYPE, GUILD_STYLE, GUILD_NAME))
  {
    case 1: 
        write("You begin to concentrate on your true self "+
              "and the screams of the arena audience. You are now one of "+
              "Kalak's Champions!\nGhastly hands reach out from a hole "+
               "in the ceiling, holding a cuirasse "+
              "while a tiny child, in the rags of a slave, runs up "+
              "and steals a piece of your clothing.\n"+
              "Barely a warrior and already the mysteries begin.\n");
        say("A small child runs up to "+QCTNAME(TP)+" and steals a "+
            "scrap of clothing. As the child runs away you can see "+
            "ghastly hands reach out from the ceiling holding a cuirasse "+
            "and reaching for "+QCTNAME(TP)+"'s neck.\nWhat is going on "+
            "here?\n");
        break;
    case -4:
        NF("Your other guilds won't let you throw away you freedom so "+
           "easily. Or perhaps its that you don't have any already.\n");
        return 0;
    default:
        NF("Couldn't join you...please notify a wizard.\n");
        return 0;
  }

    TP->setup_skill_decay();
  SET_GBIT(TP, PSION_MEMBER);
  TP->clear_guild_stat(SS_OCCUP);

  if (!IS_WIZ(TP) && extract(TP->query_real_name(), -2) != "jr")
  {
    if (file_size(file = MEM_FILE(TP->query_real_name())) >= 0)
      rm(file);

    write_file(file, sprintf("%|76s\n%|76s\n\n",
        TP->query_cap_name(), "Joined " + ctime(time())));

    WRITE_LOG(JOIN_LOG, TP, "has just joined the guild.");
    call_other(MANAGER, "add_member", TP->query_real_name());
  }
  if(member_array(PSION_SOUL,TP->query_cmdsoul_list())<0)
    TP->add_cmdsoul(PSION_SOUL);
  TP->update_hooks();


  CO(PSION_OBJ + "amulet.c")->move(TP, 1);
  return 1;
}

int update(string str)
{
  object sh, amul;
  int sk, i, bits;
  string str1, str2, str3, name, file, when;
  mixed tmp;
 
    NF("To refresh your mind, use <update membership>.\n");
  if (str != "membership")
    return 0;

  NF("But you aren't a member!\n");
  if (!IS_MEMBER(TP))
    return 0;

  TP->remove_guild_occ();

  // Readd bit if its gone.
  if (!TEST_GBIT(TP, PSION_MEMBER)) SET_GBIT(TP, PSION_MEMBER);

  // Update shadow
  if (!(sh = CO(GUILD_SHADOW)) || 
      sh->shadow_me(TP, GUILD_TYPE, GUILD_STYLE, GUILD_NAME) != 1)
  {
    write("Couldn't update your membership...please talk to a " +
          "wiz immediately.\n");
    return 1;
  }

  // Add our cmdsoul if it's missing.
  if (member_array(PSION_SOUL, TP->query_cmdsoul_list()) < 0)
    TP->add_cmdsoul(PSION_SOUL);

  TP->update_hooks();

  // Add a cuirasse if it's missing.
  if (!present(AMUL_ID, TP))
      call_other(MANAGER, "give_amulet", TP);

  write("Ok.\n");
  return 1;
}

int
check_leave()
{
   if ((IS_MEMBER(TP)) && (!TEST_GBIT(TP, PSION_MEMBER)) && (!IS_WIZ(TP)))
  {
      write("You must choose to either update your membership or cease "+
            "being a gladiator. There is no other option.\n");
      return 1;
  }
    return 0;
}
