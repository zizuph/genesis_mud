/*
* /std/mweapon.c
* This is the standard missiles launcher
* (bow, sling, crossbow, etc.)
*/
// inherit "/std/weapon.c";
inherit "/d/Wiz/rastlin/missile/mbase";

#include <wa_types.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <tasks.h>
#include <language.h>
#include <formulas.h>
#include <macros.h>
#include <filter_funs.h>
#include <missile.h>

static int bow_class;  /* Class of bow (bow, crossbow, sling) */
static object loaded_arrow;  /* The arrow held in this object */

public int check_valid_arrow(object arrow);
public int query_ammo_class();

/*
* Function:    create_weapon
* Description: Make this weapon into a missile weapon
*/
public nomask void
create_weapon()
{
   set_hit(0);
   set_pen(0);
   set_wt(W_CLUB);
   set_dt(W_BLUDGEON);
   set_hands(W_ANYH);
   set_wf(this_object());
   load_verb = "nock";
   shoot_verb = "loose";
   aim_penalties = ({ -300, -150, -0, 50, 150 });
   bow_pen = 15;
   
   this_object()->create_mweapon();
}

/*
* Function:   create_mweapon
* Description: Default creation function (replace it)
*/
public void
create_mweapon() { }

/*
* Function:   init
* Description: Adds the missile weapon's verbs
*/
void
init()
{
   ::init();
   add_action("load","load");
   if(load_verb != "load")
      add_action("load",load_verb);
   add_action("unload","unload");
   add_action("shoot","shoot");
   if(shoot_verb != "shoot")
      add_action("shoot",shoot_verb);
   add_action("aim","aim");
   add_action("break_aim","",1);
}

/*
* Function:       query_damage
* Returns:        int damage (that this weapon does)
* Note:           Redefined from mbase.c to include the
*                 effectiveness of the loaded projectile
*/
public int
query_damage()
{
   int damage;
   
   damage = ::query_damage();
   damage += (damage * loaded_arrow->query_damage_mod()) / 100;
   return damage;
}

/*
* Function:     two_hands_free
* Description:  Does the player have two free hands?
* Arguments:    none
* Returns:      1 If the player has two free hands to load this
*               weapon with, 0 otherwise
*/
public int
two_hands_free()
{
   object ob;
   
   /* Return If they are wielding a weapon that isn't this one */
   if((ob = this_player()->query_armour(TS_RWEAPON))
         && ob != this_object())
   {
      notify_fail("You can't '"+query_verb()+"' with " +
            LANG_ADDART(ob->short()) + " in your right hand.\n");
      return 0;
   }
   if((ob = this_player()->query_armour(TS_LWEAPON))
         && ob != this_object())
   {
      notify_fail("You can't '"+query_verb()+"' with " +
            LANG_ADDART(ob->short()) + " in your left hand.\n");
      return 0;
   }
   /* Do I need to check W_BOTH?  I already know they're wielding */
   /* this_object() in at least one hand.. */
   
   return 1;
}

/*
* Function:     load
* Description:  Tries to load a projectile matching str
*               into this weapon
* Arguments:    string str
* Returns:      0/1 (standard action)
*/
public int
load(string str)
{
   mixed *obs;
   object arrow;
   int index;
   
   notify_fail("You're not wielding the "+short()+".\n");
   if(query_wielded() != this_player())
      return 0;
   
   notify_fail("But you're under attack!\n");
   if(check_under_attack(this_player()))
      return 0;
   
   notify_fail("The "+short()+" is already loaded.\n");
   if(loaded_arrow)
      return 0;
   
   if(!two_hands_free())
      return 0;
   
   notify_fail("Couldn't find any '"+str+"' to load the " +
         short()+" with.\n");
   if(!parse_command(str,all_inventory(this_player()),"[a] [a] [the] %i",obs))
      return 0;
   
   /*
   write("Value: "+obs[0]+"   Objects: "+(sizeof(obs)-1)+"\n");
   */
   
   /* Find the first item which matches the description */
   index = 0;
   while((++index < sizeof(obs)) && (!arrow))
   {
      /*
      */
      if(obs[index]->check_valid_bow(this_object()) && check_valid_arrow(obs[index]))
         arrow = obs[index];
   }
   notify_fail("You can't load the "+short()+" with that.\n");
   if(!arrow)
      return 0;
   
   /* Feed the projectile into the bow */
   loaded_arrow = arrow;
   if(loaded_arrow->query_prop(HEAP_I_IS))
      loaded_arrow->split_heap(1);
   loaded_arrow->move(this_object(),1);  /* ? */
   write("You "+load_verb+" "+loaded_arrow->short()+".\n");
   say(QCTNAME(this_player())+" " + LANG_PWORD(load_verb) + " " +
      LANG_ADDART(loaded_arrow->short())+".\n");
   
   return 1;
}

/*
* Function:     unload
* Description:  unloads any projectiles in the bow
* Arguments:    string str
* Returns:      0/1 (standard action)
*/
int
unload(string str)
{
   notify_fail("It's not loaded.\n");
   if(!loaded_arrow)
      return 0;
   
   loaded_arrow->move(environment(),1);
   write("You unload "+loaded_arrow->short()+".\n");
   say(QCTNAME(this_player())+" unloads "+loaded_arrow->short() +
      " from "+this_player()->query_possessive()+" "+short()+".\n");
   loaded_arrow = 0;
   return 1;
}

/*
* Function:    check_valid_arrow
* Description: Determines If a projectile can be used in
*              this missile weapon.
* Arguments:   object arrow
* Returns:     1 If it's acceptable ammo, 0 otherwise
*/
public int
check_valid_arrow(object arrow)
{
   /* It's a valid projectile If it's the same type of ammo */
   /* as this weapon uses. */
   if(arrow->query_broken())
      return 0;
   return (arrow->query_ammo_class() == query_ammo_class());
}

/*
* Function:  query_bow_class
* Returns:   Type of missile weapon (M_BOW, M_CROSSBOW, etc.)
*/
public int
query_bow_class()
{ return bow_class; }
/*
* Function:  set_bow_class
* Arguments: int class
*            Type of missile weapon (M_BOW, M_CROSSBOW, etc.)
*/
public void
set_bow_class(int i)
{ bow_class = i; }

/*
* Function:  query_ammo_class
* Returns:   Type of ammo needed
*/
public int
query_ammo_class()
{
   if(bow_class == M_STAFFSLING)
      return M_STONE;
   return bow_class;
}

/*
* Function:    remove_object()
* Decription:  destroys the bow, but first moves the arrow to
*              the environment
*/
public void
remove_object()
{
   if(loaded_arrow)
      {
      loaded_arrow->move(environment());
      if(present(loaded_arrow))
         loaded_arrow->remove_object();
   }
   ::remove_object();
}

/*
* Function:     short
* Description:  Describes the bow and any loaded ammo
* Arguments:    object for_obj
*               The object seeing this object
* Returns:      string short_description
*/
public varargs string
short(object for_obj)
{
   return ( loaded_arrow ? "loaded " : "" ) + ::short(for_obj);
}

/*
* Function:   long
* Description: describes the missile weapon and its projectile
* Arguments:   string str, object for_obj
* Returns:     Uh.. dunno.
*/
varargs public mixed
long(string str, object for_obj)
{
   return ::long(str,for_obj) +
   ( loaded_arrow ? "It is loaded with " +
      loaded_arrow->short() + ".\n" : "");
}

/*
* Function:     unwield
* Description:  called from /std/weapon when this is unwielded
*               - makes sure that the projectile falls out
* Arguments:    none
* Returns:      0 to ensure the regular function gets called
* Note:         IF YOU MASK THIS, CALL ::unwield() IN THE BODY OF
*               THE FUNCTION
*/
int
unwield()
{
   if(!loaded_arrow)
      return 0;
   
   set_alarm(0.0,0.0,"dump_loaded_arrow");
   disrupt_aim(0);
}

void
dump_loaded_arrow()
{
   tell_room(environment(this_player()),
      capitalize(loaded_arrow->short()) +
      " falls out of it.\n");
   loaded_arrow->move(environment(this_player()),1);
   loaded_arrow = 0;
   return 0;
}

/*
* Function:     set_load_verb
* Description:  sets the verb used to load this weapon
* Arguments:    string verb
* Returns:      void
*/
void
set_load_verb(string verb)
{ load_verb = ( strlen(verb) ? verb : "nock" ); }

/*
* Function:     query_load_verb
* Description:  the verb used to load this weapon
*/
public string
query_load_verb()
{ return load_verb; }

/*
* Function:        aim_consider
* Description:     Extra considerations for aiming
* Returns:         0 If aiming allowed, 1 otherwise
* Note: If you redefine this, call ::aim_consider();
*/
public
public int
aim_consider()
{
   if(!two_hands_free())
      return 0;
   
   notify_fail("Your " + short() + " isn't loaded.\n");
   if(!loaded_arrow)
      return 0;
   
   return 1;
}

/*
* Function:       fire_dIfficulty_consider
* Description:    Any additional bonuses associated with firing
* Returns:        The bonus
*/
public int
fire_difficulty_consider()
   {
   int bonus;
   
   bonus = loaded_arrow->query_accuracy();
   return bonus;
}

/*
* Function:     shoot_consider
* Description:  Any extra considerations for allowing shooting
* Returns:      1 If allowed, 0 otherwise
*/
public int
shoot_consider()
{
   if(!two_hands_free())
      return 0;
   
   notify_fail("Your "+short()+" isn't even loaded.\n");
   if(!loaded_arrow)
      return 0;
   
   return 1;
}

void
shoot_message()
{
   string msg;
   
   // Tell the firer
   query_wielded()->catch_msg("You "+query_verb()+" "+
      loaded_arrow->short() +
      " from your "+short());
   // Tell the firer's env, including the target If he's there
   tell_room(environment(this_player()),
      QCTNAME(this_player())+" "+LANG_PWORD(shoot_verb)+" "+
      loaded_arrow->short() +
      " from "+this_player()->query_possessive() +
      " "+short(), ({ this_player() }) );
   
   if(firing_distant())
      {
      object * cansee;
      
      // MESSAGES TO THE FIRER'S ROOM
      tell_room(environment(this_player()), " " +
         distant_descs(this_player(),target)[0]);
      
      // MESSAGES TO THE TARGET AND HIS OR HER ENV
      cansee = FILTER_LIVE(all_inventory(environment(target)));
      
      msg = (QCTNAME(this_player()) +
         " " + LANG_PWORD(shoot_verb)+" " +
         loaded_arrow->short() +
         " " + distant_descs(this_player(),target)[1]);
      if(firer_visible())
         filter(cansee,&can_see_distant(,this_player()))->
      catch_msg(msg);
      
      msg = (capitalize(loaded_arrow->short()) +
         " flies in " +
         distant_descs(this_player(),target)[1]);
      if(!firer_visible())
         cansee->catch_msg(msg);
      else
         filter(cansee,not @ &can_see_distant(,this_player()))->
      catch_msg(msg);
   }
}

public int
hurt_message(mixed result)
{
   string what, who, join, where, how;
   int dt;
   
   dt = loaded_arrow->query_ammo_dt();
   loaded_arrow->move(target,1);
   
   who = QTNAME(target);
   where = result[1];
   join = " on the ";
   
   switch (result[0])
   {
      case 0..4:
      how = ".";
      what = (dt==W_BLUDGEON ? "brushing" :
         (dt==W_SLASH ? "scraping" : "jabbing"));
      break;
      case 5..9:
      how = ".";
      what = (dt==W_BLUDGEON ? "bruising" :
         (dt==W_SLASH ? "cutting" :"stabbing"));
      break;
      case 10..19:
      how = (dt == W_IMPALE ? ", hard." : ".");
      what = (dt==W_BLUDGEON ? "hitting" :
         (dt==W_SLASH ? "slicing" : "stabbing"));
      break;
      case 20..29:
      how = (dt==W_BLUDGEON ? ", rather hard." : 
         (dt==W_SLASH ? ", rather deeply." : "."));
      what = (dt==W_BLUDGEON ? "hitting" :
         (dt==W_SLASH ? "slicing" : "piercing"));
      break;
      case 30..49:
      how = (dt==W_BLUDGEON ? ", very hard." :
         (dt==W_SLASH ? ", very deeply." : ", deeply."));
      what = (dt==W_BLUDGEON ? "hitting" :
         (dt==W_SLASH ? "slicing" : "piercing"));
      break;
      case 50..69:
      how = (dt==W_IMPALE ? ", very deeply." : ".");
      what = (dt==W_BLUDGEON ? "smashing" :
         (dt==W_SLASH ? "slashing" : "piercing"));
      break;
      case 70..89:
      how = (dt==W_BLUDGEON ? ", with a bone-crushing sound." :
         (dt==W_SLASH ? ", open." : "."));
      what = (dt==W_BLUDGEON ? "smashing" :
         (dt==W_SLASH ? "slashing" : "impaling"));
      join = where = "";
      break;
      default:
      how = (dt==W_BLUDGEON ? ", brutally." :
         (dt==W_SLASH ? ", wide open." : ", completely."));
      what = (dt==W_BLUDGEON ? "crushing" :
         (dt==W_SLASH ? "cleaving" : "impaling"));
      join = where = "";
   }
   
   target->catch_msg(", " + what + " you" + join +
      where + how + "\n");
   
   {
      object * observers, * fguys, * tguys;
      
      fguys = FILTER_LIVE(all_inventory(environment(this_player())));
      tguys = FILTER_LIVE(all_inventory(environment(target)));
      // Array union, no duplicates
      observers = (fguys - tguys) + tguys;
      observers -= ({ target });
      
      filter(observers, &can_see_distant(,target))->
      catch_msg(", " + what + " " + who + join + where +
         how + "\n");
      
      filter(observers, not @ &can_see_distant(,target))->
      catch_msg(".\n");
   }
   
   return 0;
}

void
miss_message()
{
   string msg;
   
   object * observers, * fguys, * tguys;
   
   fguys = FILTER_LIVE(all_inventory(environment(this_player())));
   tguys = FILTER_LIVE(all_inventory(environment(target)));
   // Array union, no duplicates
   observers = (fguys - tguys) + tguys;
   observers -= ({ this_player(), target });
   
   target->catch_msg(" at you but misses.\n");
   
   msg = " at " + QTNAME(target) + " but miss";
   this_player()->catch_msg(msg + ".\n");
   filter(observers, &can_see_distant(,target))->
   catch_msg(msg + "es");
   
   observers->catch_msg(".\n");
   
   loaded_arrow->move(environment(target),1);
}

void
shoot_post_message()
{
   if(random(100) < loaded_arrow->query_likely_break())
      loaded_arrow->set_broken();
   loaded_arrow = 0;
}

/*
 * Function Name: query_loaded
 * Description:   gives the object that the weapon is loaded with.
 * Returns:       the object the weapon is currently loaded with or 0;
 */
object
query_loaded()
{
   return loaded_arrow;
}

