// file: card
// creator: Ilyian, October 11, 1995
// purpose: Base card for the Deck of Cahor
// note:
// todo:

inherit "/std/object";
#include "/d/Avenir/common/common.h"
#define LIVE_I_USING_CARD   "_live_i_using_card"

/* Prototypes */
int hold_me(string str);
int query_allowed();
int query_fail();
void set_myadj(string newadj);
void set_mycolor(string newcolor);
void set_mana_cost(int new_mana);
void do_effect();
void success_effect();

string myadj = "uninteresting";
string mycolor = "white";
int mana_cost = 20; // Default mana cost
object tp;
int time_to_effect = 5;
int effect_alarm; 

void create_object()
{
    set_name("card");
    add_name("_avenir_card");
    set_adj(({myadj, mycolor}));
    set_short(myadj+" "+mycolor+" card");

    set_long("This card is completely uninteresting.\n");

    add_prop(MAGIC_AM_MAGIC,({40, "enchantment"}));

    add_prop(MAGIC_AM_ID_INFO,({
       "The "+short()+" seems to be quite magical.\n",1,
       "Holding it against the forehead activates its magic.\n",10,
       "\n",30}));

    add_prop(OBJ_S_WIZINFO,"This card is one of the "
        +"cards given out by the Cahor quest in Avenir. It "
        +"is autoloadable, but it can only be use once, and "
        +"then it is destroyed.\n"
        +"Its effect is: ");

    add_prop(OBJ_I_WEIGHT, 2);
    add_prop(OBJ_I_VOLUME, 10);
    add_prop(OBJ_I_VALUE, 0);
}

string query_auto_load() { return MASTER + ":"; }

init()
{
   add_action(hold_me,"hold",0);
   ::init();
}

int hold_me(string str)
{
   if(!str || str=="")
     return 0;

   if(str=="first card" || str=="second card" ||
      str=="third card" || str=="fourth card" ||
      str=="fifth card" || str=="sixth card")
     {
      write("You will need to be more specific than that.\n");
      return 1;
      // Ok, so I am too lazy to work out a command parser
     }

   if(str=="card" || 
      str==query_short() || str==mycolor+" card" || 
      str==myadj+" card"  || str==mycolor+" "+myadj+" card")   
     {
      tp = this_player();

      if( !query_allowed() )
        {
            return 1;
        }

      else

        {
          write("You hold the "+query_short()+" against "
               +"your forehead and concentrate on its "
               +"power.\n");
          say(QCTNAME(tp)+" holds a "+query_short()+" against "
              +tp->query_possessive()+" forehead.\n");
          tp->add_prop(LIVE_I_USING_CARD,1);
          effect_alarm = set_alarm(itof(time_to_effect),0.0,do_effect);
          return 1;
         }
     }
   return 0;
}

void set_mana_cost(int new_mana)
{
    mana_cost = new_mana;
    return;
}

void set_myadj(string newadj)
{
    myadj = newadj;
}

void set_mycolor(string newcolor)
{
    mycolor = newcolor;
}


/* 
 * Prevention measures, which prevent even beginning
 * to try to use the card. Returns 1 if you can
 * use the card, 0 if you cannot. 
 */
int query_allowed()
{
    if(effect_alarm)
      {
       write("You are already trying to use the "+query_short()+"!\n");
       return 0;
      }
    if(tp->query_prop(LIVE_I_USING_CARD))
      {
       write("You are already concentrating on another "
            +"card!\n");
       return 0;
      }
   return 1;
}

/*
 * Why the card would fail to work...
 * Returns 1 of you will fail, 0 if you succeed.
 */
int query_fail()
{
   if(tp->query_mana() < mana_cost)
       {
         write("You do not have the mental energy.\n");
         return 1;
       }
    // Other possible fails here...
    return 0;
}

/* 
 * Do_effect should probably never be redefined, since
 * all it does is decrease the player's mana, and 
 * call success_effect(), where the actual effect is
 * coded.
 */
void do_effect()
{
      effect_alarm = 0;
      tp->remove_prop(LIVE_I_USING_CARD);
      if(  query_fail() )
            return;
      else
         {
           tp->add_mana(- mana_cost );
           success_effect();
           return;
          }
   return 0;
}

/*
 * The actual effect goes in here.
 */
void success_effect()
{
    write("Nothing seems to happen.\n");
    remove_object();
    return;
}

