// converted to /lib/wearable_item by Lilith 09 Jul 1998
// converted to use item_expiration, code cleanup--Lilith, May 2022

inherit "/std/object";
inherit "/lib/wearable_item";
inherit "/lib/keep";

#include <wa_types.h>
#include <macros.h>
#include <stdproperties.h>

string nam, size, tnt;
string randsize();

void set_nam(string str)  {    nam = str;    }
void set_size(string str) {    size = str;   }
void set_tnt(string str)  {    tnt = str;    }

void
init_the_girdle()
{
    if (!size) size = randsize();
    if (!nam)  nam = one_of_list(({"hip girdle","hip belt","mekhala"}));
    if (!tnt)  tnt = one_of_list(({"gold","silver","bronze","platinum",
                 	"brass","copper","leather","webcloth"}));

    set_adj(({nam, tnt, size}));
    set_short(tnt +" "+ nam +" decorated with "+ size +"");
    set_long("This "+ nam +" is very lovely. It is currently in high "+
           "fashion in the Forbidden City of Sybarus, worn by the "+
           "Sybarite noblewomen after the fashion of the Goddess "+
           "Jazur as an enhancement to their beauty and desirability. "+
           "Worn low about the waist or hips, the "+ nam +" can accent "+
           "various states of dress or undress, as the wearer wishes. "+
           "The "+ tnt +" is of the highest possible quality, and the "
           + size +" are simply there for ornamentation.\n"+
           "   It is an item of clothing that may be worn in addition to "+
           "armour.\n");
}

/************ creation **************/
void
create_object()
{
    config_wearable_item(A_HIPS, 1, 1, this_object());
    set_keep(1);

    if (!nam)
        init_the_girdle();

   set_name("bazaar_girdle");
   add_name(({"belt", "girdle"}));
   add_adj(({"sybarun", "sybarite"}));
   add_name(nam);
   add_name(size);
   if (nam = "mekhala");
        add_name("mekhala");
   add_pname(({"clothes", "clothing"}));
    
   add_prop(HEAP_S_UNIQUE_ID, "girdle_" + tnt + "_" + nam);
   add_prop(OBJ_I_VOLUME, 200);
   add_prop(OBJ_I_WEIGHT, 500); 
   add_prop(OBJ_I_VALUE, 250);
   
   if (IS_CLONE)
      set_item_expiration();  
}             

string
randsize()
{
   string str;

   switch(random(5))
   {   
      case 0:  
      {    
           add_item(({"tiny bells", "tiny bell"}),
              "The bells are quite tiny! They depend from the edges of "+
              "the "+ nam +" and make a high-pitched tinny noise whenever "+
              "moved.\n");
           str="tiny bells";
      }        
      break;
      
      case 1: 
      {
          str="glass beads";       
          add_item(({"beads", "glass beads"}), 
              "The they have been expertly set the into the "+ tnt +
              " of the "+ nam +". Though not of the highest possible "+
               "quality, each one is as large as your thumbnail.\n");
      }
      break;
      
      case 2: 
      {
             add_item(({"scarves", "silk scarves", "scarf"}),
                 "The silk scarves are multicoloured and almost transparent. "+
                 "They are well-attached to the "+ nam +", and seem to float "+
                 "in the air.\n");
             str="silk scarves";      
      }
      break;

      case 3: 
      {
           add_item(({"pearls", "pearl"}),
               "The pearls are small and perfectly round. They are expertly "+
               "set into the "+ tnt +" of the "+ nam +".\n");
           str="pearls";
      }
      break;

      case 4: 
      {    
           add_item(({"thin chains", "thin chain"}),
               "There are several thin metal chains attached to the "+nam +
               ". They sway with every movement and catch the light.\n");
           str="thin chains";       
      }
      break;
   }
   return str;                                                                               
}

/*
 * Function name: leave_env
 * Description:   The clothing is moved from the inventory.
 * Arguments:     from - Where from  to - Destination.
 */
void
leave_env(object from, object to)
{
    wearable_item_leave_env(from, to);
    ::leave_env(from, to);
}

/*
 * Function name: query_my_recover
 * Description:   Return the recover strings for changing armour variables.
 * Returns:       Part of the recoder string
 */
string
query_my_recover()
{
    string rec;
    rec = MASTER + ":";
    rec += "#nam#" + nam;
    rec += "#size#" + size;
    rec += "#tnt#" + tnt;
    rec += query_item_expiration_recover();
    return rec;
}

/*
 * Function name: init_my_recover
 * Description:   Initialize the armour variables at recover.
 * Arguments:     arg - The recover string as recieved from query_arm_recover()
 */
void
init_my_recover(string arg)
{
    string dummy;
    sscanf(arg, "%s#nam#%s#%s", dummy, nam, dummy);
    sscanf(arg, "%s#size#%s#%s", dummy, size, dummy);
    sscanf(arg, "%s#tnt#%s#%s", dummy, tnt, dummy);
    init_item_expiration_recover(arg);   
    init_the_girdle();
}

/*
 * Function name: query_recover
 * Description  : Called to check whether this armour is recoverable.
 *                If, for some reason, you do not want your armour to
 *                recover, you should define the function and return 0.
 * Returns      : string - the default recovery string.
 */
public string
query_recover()
{
    return MASTER + ":" + query_my_recover();
}

/*
 * Function name: init_recover
 * Description  : When the object recovers, this function is called to set
 *                the necessary variables. 
 * Arguments    : string argument - the arguments to parse
 */
public void
init_recover(string arg)
{
    init_my_recover(arg);
}


void
appraise_object(int num)
{
    ::appraise_object(num);
    appraise_wearable_item();
}
