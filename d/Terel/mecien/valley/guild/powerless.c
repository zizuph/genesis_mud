/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
/* This comment tells emacs to use c++-mode -*- C++ -*- */


/* The mystic silver ring */
inherit "/std/spells";
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include "/secure/std.h"
#include "/d/Terel/mecien/valley/guild/mystic_defs.h"

#define TP              this_player()
#define TO              this_object()
#define ETO             environment(TO)
#define ALCHECK(xx)     ((xx)->query_alignment() >= JOIN_LIM)
#define TRUE_MEMBER(xx) (MEMBER(xx) && ALCHECK(xx) && QM_RANK(xx) >= 0)

/*
* Global variables
*/

string spell_verb;
int id_destroy = 0;

/*
* Prototypes
*/
public void soul(object ob);
public int allowed(object ob);
public void update_spells(object ob);
public void destroy_ring();
private string pad(string str, int z_length);

public string
query_recovery(){ return 0; }

/*
* Function name: query_auto_load
* Description:   Make this object autoloading
* Returns:       The filename of this object
*/
public string
query_auto_load()
{
    /*
     * the :2 is just so init_arg will get called.
     */
	    
   return MASTER + ":" + 2;
}


/*
* Function name: update_spells
* Description:   update the list of spells available to the player
*                add spells via add_spell
* Arguments:     ob - the player 
*/
public void
update_spells(object ob)
{
}

/*
* Function name: create_spells
* Description:   Initialization function
*/
void
create_spells()
{
   set_name(({"Mystic_ring","ring"}));
   set_adj(({"silver","mystic"}));
   set_short("silver ring");
   set_pshort("silver rings");
   
   set_long("A simple silver ring inscribed with an intricate star.\n");
   
   add_prop("no_sacrifice", 1);
   
   add_prop(OBJ_I_VALUE, 0);
   add_prop(OBJ_I_WEIGHT, 0);
   add_prop(OBJ_I_VOLUME, 0);
}


int
cast_spell(string str)
{
   string spell_file;
   
   if (allowed(TP)) 
      {
      seteuid(getuid());
      spell_file = SPELL_DIR + spell_verb;
      return call_other(spell_file, spell_verb, str);
   } 
   else 
      {
      set_alarm(4.0, -1.0, "delay_msg", TP);
      return 0;
   }
}

/*
* Function name: query_spell_time
* Description:   How long time will it take to cast a spell?
* Arguments:  verb - The spell verb
* Returns:       The time it will take. Real casting time will be time + 2 
*/
int
query_spell_time(string verb)
{
   spell_verb = verb;
   if (verb == "perditus") return 4;
   if (verb == "portus") return 10;
   if (verb == "immuto") return 10;
   return 0;
}

void
enter_env(object new, object old)
{
   ::enter_env(new, old);
   if (!living(new)) return;
   if (allowed(new)) 
      set_alarm(2.0, -1.0, "soul", new);
   else
      set_alarm(2.0, -1.0, "delay_msg", new);
   
   return;
}

void
delay_msg(object new)
{
   TO->move(environment(new));
   if (MEMBER(new)) 
      {
      tell_object(new, "Because of your evil actions the " +
         TO->short() + " slips away from you.\n");
      new->remove_cmdsoul(MYSTIC_SOUL);
      new->update_hooks();
   } 
   else 
      {
      tell_object(new, "You are not entitled to have the " +
         TO->short() + "!\n");
      tell_object(new, "You feel forced to drop it.\n");
   }
   tell_room(environment(new), QCTNAME(new) + " drops a " +
      short() + ".\n", new);
   if (!id_destroy) id_destroy = set_alarm(10.0, -1.0, "destroy_ring");
}

public void
soul(object ob)
{
   int rank, i;
   string *soul_list;
   object shadow;
   
   if (!ob || !living(ob)) return;
   
   seteuid(getuid());
   if (environment(TO) == ob) 
      {
      if (ob->query_alignment() >= JOIN_LIM + 30) 
         {
         if (ob->query_present_rank() || T_WIZ(ob))
            {
            ob->catch_msg("You are a dedicated disciple " +
               "of the Ancient Ones.\n");
          }
         else
            {
            rank = ob->query_mystic_rank();
            ob->catch_msg("You do not fulfill the requirements of a " +
               RANKTITLE[rank] + ".\n");
            ob->catch_msg("You lose some of your spells.\n");
          } 
       } 
      else 
         {
         ob->catch_msg("Thou art close to losing the powers of " +
            "the Ancient Ones.\n");
       }
   }
   update_spells(ob);
   
   
   /*
   * We need to have the mystic soul as the first soul in the list
   * of command souls.  I wish there was a better way to do this.
   */
   
   if (ob->query_wiz_level() == WIZLEV_MORTAL)
      {
      soul_list = ob->query_cmdsoul_list();
      for (i = 0; i < sizeof(soul_list); i++)
      ob->remove_cmdsoul(soul_list[i]);
      ob->add_cmdsoul(MYSTIC_SOUL); 
      /*ob->add_cmdsoul("/d/Terel/common/mystic/mystic_soul");*/
      for (i = 0; i < sizeof(soul_list); i++)
      ob->add_cmdsoul(soul_list[i]);    
      ob->update_hooks();
   }
   
   /*
   * Here is the temp fix to make sure mystics get the new lay shadow
   */
   
   if (member_array("/d/Terel/mecien/valley/guild/mystic_lay_sh:",
            ob->query_autoshadow_list()) == -1) {
      
      shadow = clone_object("/d/Terel/mecien/valley/guild/mystic_lay_sh"); 
      if (shadow->shadow_me(TP, "layman", "mage",
               "The Ancient Mystic Mages")!=1){
         ob->catch_msg("There is a problem with the mystics\n");
         ob->catch_msg("please mail Sorgum, Mecien or Mortricia.\n");
         "/secure/master"->do_debug("destroy", shadow);      
         return 0;
       }
   }
   
}

public int
allowed(object ob)
{
   if (T_WIZ(ob)) return 1;
   if (TRUE_MEMBER(ob)) return 1;
   return 0;
}

public void
destroy_ring()
{
   if (ETO->query_prop(ROOM_I_IS))
      tell_room(ETO, "The "+short()+" vanishes.\n");
   remove_object();
}

/*
* Function name: list_spells
* Description:   This function is called to list the spells from
*                the player soul when the command "spells" is typed.
*/
public void
list_spells()
{
   int i, i1, vsize, vlim, fold;
   string s1, s2;
   
   vsize = sizeof(verb_list);
   vlim = vsize;
   fold = vsize/2;
   if (vlim > fold) vlim = fold;
   if (vlim + fold == vsize - 1)
      {
      vlim++;
      fold++;
   }
   write("------------------------*** The Ancient Mystic Order " +
      "***----------------------\n");
   for (i = 0; i < vlim; i++)
   {
      s1 = pad(verb_list[i], 15) + pad(name_list[i], 21);
      i1 = fold + i;
      if (vsize != vlim && i1<vsize)
         {
         s2 = pad(verb_list[i1], 15) + name_list[i1];
         write(s1 + " | " + s2 + "\n");
        }
      else
         {
         write(s1 + " |\n");
        }
   }
   write("-----------------------------------------------------" +
      "-------------------------\n");
}

private string
pad(string str, int z_length)
{
   string space;
   
   space = "                                                 ";
   return str + extract(space, 0, z_length - strlen(str));
}

int
query_spell_mess(string verb)
{
   write("You start to focus your attention on the powers of the " +
      "Ancient Ones.\n");
   say(QCTNAME(TP) + " focuses " + TP->query_possessive() +
      " attention on something mysterious.\n");
   return 1;
}


/*
* Function name: init_arg
* Description:   Called when autoloading
*/
void
init_arg(string str)
{
   set_alarm(3.0, -1.0, "notify_icon_holders");
}

/*
* Function name: notify_icon_holders
   * Description:   send a message to all guildmembers logged in
*/
void
notify_icon_holders()
   {
   object *ul;
   int i;
   
   ul = users();
   for (i = 0; i < sizeof(ul); i++)
   if (MEMBER(ul[i]) && present(MYSTIC_ICON, ul[i]) && ul[i] != ETO)
      ul[i]->catch_msg("You feel the holy icon grow warm.\n");
}
