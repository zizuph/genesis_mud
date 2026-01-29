
// file name: coffin.c
// creator(s): Ilyian, October 6, 1995
// last update: Ilyian, Oct. 9, Added more functionality
//               to the coffin itself so it can easily
//               be remade to be used in other 
//               circumstances.
//              Cirion, Feb 1996, redid most of it, put in
//               some parsing.
// purpose: A coffin that players can enter so they can
//          get into the Isle of the Dead. See
//          /d/Avenir/common/dead/dead.doc for more
//          details
// note:
// bug(s):
// to-do:

inherit "/std/receptacle";

#include "/d/Avenir/common/ships/dead/deadship.h"
#include <cmdparse.h>
#include <language.h>

int keepshut;
string *adjs = (({"heavy", "massive", "large", "long", "oblong",
                   "thick"}));
string *types = (({"wooden", "oak", "pine", "mahogany"}));
string adj, type, my_id;

int config_coffin()
{
   adj = adjs[random(sizeof(adjs))];
   set_adj(adj);
   type = types[random(sizeof(types))];
   add_adj(type);

   set_short(adj+" "+type+" coffin");   
   set_pshort(adj+" "+type+" coffins");
   add_name(COFFNAME);
   return 1;
}

create_container()
{
   set_name(({"coffin"}));
   set_pname("coffins");
   add_name(({"sarcouphagus","lid"}));

   config_coffin();

   AI(({"lid","cover"}),"The cover is of thick and heavy wood.\n");

   add_item(({"view","outside","out"}),"@@coffin_view");

   set_long("@@coffin_long");

   add_prop(CONT_I_IN,1);
   add_prop(CONT_I_WEIGHT, 10000);
   add_prop(CONT_I_VOLUME, 120000);
   add_prop(OBJ_I_VALUE, 1860);
   add_prop(CONT_I_IN,1);
   add_prop(CONT_I_RIGID,0);
   add_prop(CONT_I_TRANSP,0);
   add_prop(CONT_I_MAX_VOLUME, 120000);
   add_prop(CONT_I_MAX_WEIGHT, 150000);
   add_prop(CONT_I_LIGHT, "@@check_light");
   add_prop(CONT_I_CLOSED, 0);
   add_prop(OBJ_M_NO_GET, "@@check_get");
   add_prop(OBJ_S_WIZINFO,
      "This is a coffin that players can enter, and "
     +"allow them passage onto the Isle of the Dead in "
     +"Avenir. Players should not be able to carry it "
     +"around.\n");
}

string id_name()
{
   return my_id;
}

int set_id_name(string what)
{
   my_id = COFFNAME + what;
   add_name(my_id);
}

int check_light()
{
   if(query_prop(CONT_I_CLOSED))
    return 0;
   else
    return 1;
}

mixed check_get()
{
   if(!interactive(TP) && TP->id("deadislandcoffin_bearer"))
       return 0;
   else
       return 0;
//       return "The "+short()+" is too heavy.\n";
}

void
bring_in_corpse()
{
        object corpse;
        string *races = (({"elf", "gnome", "dwarf", 
                           "goblin", "human"}));
        string *adjs = (({"tall", "noble", "small", "fair",
                          "slender", "large"}));
        string *killers = (({"jadestone", "hiranth", "kelzar",
                             "shelint", "parkath", "qualita",
                             "teriknas", "erinstu", "elipka"}));
        string *killer_nonmet = (({"raven-haired elf",
                             "slender elf", "massive troloby",
                             "tall human", "grim dwarf", 
                             "beautiful human", "sad gnome",
                             "massive human", "sad troboby"}));
        int killer;
        string title;

        remove_prop(CONT_I_CLOSED);
        seteuid(getuid());
        corpse = clone_object("/std/corpse");
        title = adjs[random(5)]+" "+ races[random(6)];
        corpse->set_name("corpse");
        corpse->set_short("corpse of a "+title);
        corpse->set_long("This is the dead body of a "+title+".\n");
        corpse->change_prop(CONT_I_WEIGHT, 40000 + random (30000));
        corpse->change_prop(CONT_I_VOLUME, 40000 + random (30000));
        corpse->add_prop(CORPSE_S_RACE, races[random(5)]);
        corpse->add_prop(CONT_I_TRANSP, 1);
        corpse->change_prop(CONT_I_MAX_WEIGHT, 190000);
        corpse->change_prop(CONT_I_MAX_VOLUME, 190000);
        killer = random(9);
        corpse->add_prop(CORPSE_AS_KILLER,
                         ({ killers[killer],
                            killer_nonmet[killer] }) );
        corpse->move(this_object());
        add_prop(CONT_I_CLOSED,1);
        return;
}

/*
 * keep_shut(1) should be called whenever the object
 * cannot be opened for some reason. (eg. something is
 * on top of it, or it is in a players inventory, so the
 * someone leaving the container will not end up in
 * someone else's inventory!!!)
 */
void
keep_shut(int shut)
{
   keepshut = shut;
   add_prop(CONT_I_CLOSED, 1);
   return;
}


init()
{
   add_action("do_leave","climb",0);
   add_action("do_leave","leave",0);
   add_action("do_enter","enter",0);
   add_action("do_nolight","light",0);
   add_action("do_inopen","open",0);
   add_action("do_inclose","close",0);
   add_action("do_inshout","shout",0);

   ::init();
}

do_inshout(string str)
{
   if (str == "" || !str)
      return 0;

   if(TO != ENV(TP))
    {
      return 0;
    }

   if(TO->query_prop(CONT_I_CLOSED))
    {
      write("Your shouts are muffled by the lid of the "
           +short()+".\n");
      tell_room(ENV(TO),"Muffled shouts can be heard from "
           +"withing the "+short()+"\n");
      return 1;
    }
  tell_room(ENV(TO), "From within the "+short()+" you "
           +"hear a voice shout: "+str+"\n");
  return 0;
}

do_inopen(string str)
{
   if (str == "" || !str)
      return 0;

   if (TO != ENV(TP))
    {
      return 0;
    }
   if(str=="coffin" || str=="lid")
    {
      if(keepshut)
         {
           write("Something is holding the lid closed.\n");
           return 1;
         }
      if(!TO->query_prop(CONT_I_CLOSED))
         {
           write("The "+query_short()+" is already open.\n");
           return 1;
         }
      write("You open the lid of the "+query_short()+".\n");
      tell_room(ENV(TO),"The lid of the "+query_short()
              +" swings open.\n");
      remove_prop(CONT_I_CLOSED);

      return 1;
    }
   NF("Open what?\n");
   return 0;
}

do_inclose(string str)
{
   if (str == "" || !str)
      return 0;

   if (TO != ENV(TP))
    {
      return(0);
    }
   if(str=="coffin" || str=="lid")
    {
      if(TO->query_prop(CONT_I_CLOSED))
         {
           write("The "+query_short()+" is already closed.\n");
           return 1;
         }
      write("You close the lid of the "+query_short()+".\n");
      tell_room(ENV(TO),"The lid of the "+query_short()
              +" swings closed.\n");
      add_prop(CONT_I_CLOSED, 1);
      return 1;
    }
  return 0;
}

do_leave(string str)
{
   if(str == "" || !str)
      return 0;

   if(str != "coffin" && str != "out" &&
      str != "out of coffin")
     {
       NF("Climb out of what?\n");
       return 0;
     }
   if(TO != ENV(TP))
    {
      return 0;
    }
   if(TO->query_prop(CONT_I_CLOSED))
    {
      write("The "+query_short()+" is closed.\n");
      return 1;
    }
  write("You climb out of the "+query_short()+".\n");
  if(!living(ENV(TO)))
       TP->move_living("M", ENV(TO));
  else
       TP->move_living("M", ENV(ENV(TO)));
  say(QCNAME(TP) + " climbs out of the "+query_short()+".\n");
  return 1;
}

int do_enter(string str)
{
   object *ob;
   int i;
   string fail_msg = "";

   if(str == "" || !str)
      return 0;

   NF("You are already inside the "+query_short()+".\n");
   if(TO == ENV(TP))
     return 0;

   NF("Enter what?\n");
   ob = normal_access(str, "%i");
   D("Normal access of "+str+": "+sizeof(ob)+"\n");
   if(!sizeof(ob))
        return 0;

   for( i = 0; i < sizeof(ob); i++ )
     {
      if(volume_left() < TP->volume())
       {
        D("No more room.\n");
        write("There is not enough room in the "+ob[i]->query_short()+".\n");
        return 1;
        }
      if(TO->query_prop(CONT_I_CLOSED))
        {
         D("Coffin is closed.\n");
         write("The "+ob[i]->query_short()+" is closed.\n");
         return 1;
        }
      if(TP->move(ob[i]))
       {
        D("Failed to move.\n");
        write("There is not enough room in the "+ob[i]->query_short()+".\n");
        return 1;
       }

    D("Entered the coffin.\n");
    tell_room(ENV(TO), QCTNAME(TP)+" enters the "+ob[i]->query_short()+".\n");
    write("You enter the "+ob[i]->query_short()+".\n");
    return 1;
      }

   D("Something strange...\n");
   NF("Enter what?\n");
   return 0;
}

public int
do_default_open(string str)
{
   if( ::do_default_open(str) )
    {
      tell_room(TO, "The lid of the coffin opens.\n");
      return 1;
    }
   return 0;
}

public int
do_default_close(string str)
{
   if( ::do_default_close(str) )
    {
      tell_room(TO, "The lid of the coffin closes.\n");
      return 1;
    }
   return 0;
}

int do_nolight(string str)
{
   if (TO != ENV(TP))
      return 0;

   if (str == "" || !str)
      return 0;

   write("It is too dangerous to start any fires in this "
        +"wood coffin.\n");
   return 1;
}

coffin_long()
{
  if (ENV(TP) == TO)
    {
      return("This coffin is dark and dank, reminding you of the "
            +"dead. The solid wood walls of the coffin "
            +"seem to be made of "+type+".\n");
    }
  else
    {
      return("This is a "+adj+" coffin, made "
            +"of solid "+type+". It might be possible "
            +"to get into it, if you were so inclined.\n");
    }
}

coffin_view()
{
   if (TO == ENV(TP))
    {
      if(TO->query_prop(CONT_I_CLOSED))
        return("The lid on the coffin is closed.\n");
      else
        return("You peer out of the coffin.\n"
              +ENV(TO)->query_long());
    }
   return("You are not inside the "+query_short()+".\n");
}


