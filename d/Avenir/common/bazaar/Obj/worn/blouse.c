// converted to /lib/wearable_item by Lilith 09 Jul 1998
inherit "/std/object";
inherit "/lib/wearable_item";
inherit "/lib/keep";

#include <wa_types.h>
#include </sys/macros.h>
#include </sys/stdproperties.h>

#define HIS  this_player()->query_possessive()

int times;
string color, type;
string randsize();
string randtnt();

void set_color(string str) {    color = str;    }
void set_type(string str)  {    type = str;     }
int  query_times()         {    return times;   }

void 
init_the_blouse()
{
    if (!color) color = randtnt();
    if (!type) type = randsize();

    set_short(color +" "+ type +" cholie");

    set_long("Among the Sybarite noblewomen, this blouse is known "+
        "as a cholie. It is cut from rich "+ type +". It is made to "+
        "fit snugly, clinging to shoulders and breasts while "+
        "while leaving the midriff bare. The sleeves are short, "+
        "ending well above the elbow, and edged with a wide "+
        "border of brocaded gold in a floral pattern. This "+         
        "particular cholie is "+ color +" in colour.\n");

    set_adj(({color, type}));
}

void
create_object()
{
	if (IS_CLONE)
        set_item_expiration();  
	
    config_wearable_item(A_TORSO, 1, 1, this_object());
    set_keep(1);

    if (!type)    init_the_blouse();

   set_name("bazaar_blouse");
   add_name(({"blouse", "cholie", "shirt"}));
   add_pname(({"clothes", "clothing"}));  
   add_adj("short");
   add_adj(({"custom", "sybarun"}));

   add_prop(HEAP_S_UNIQUE_ID, "blouse_" + color + "_" + type);
   add_prop(OBJ_I_VOLUME, 1000);   /* volume 1 litres */
   add_prop(OBJ_I_WEIGHT, 500);   /* weight 1/2 kilo */
   add_prop(OBJ_I_VALUE, 144);

   add_item(({"edge", "brocade", "pattern"}),
       "The edging of the sleeves is of brocaded gold in a pattern "+
       "of twining flowers.\n"); 
	  
}             

string
randtnt()
{
   string str;

   switch(random(19))
   {   
      case 0:  str="blue";       break;
      case 1:  str="green";      break;
      case 2:  str="red";        break;
      case 3:  str="yellow";     break;
      case 4:  str="ivory";      break;
      case 5:  str="purple";     break;
      case 6:  str="white";      break;
      case 7:  str="amethyst";   break;
      case 8:  str="aquamarine"; break;
      case 9:  str="crimson";    break;
      case 10: str="snowy";      break;
      case 11: str="ochre";      break;
      case 12: str="gray";       break;
      case 13: str="pink";       break;
      case 14: str="scarlet";    break;
      case 15: str="vermillion"; break;
      case 16: str="cream";      break;
      case 17: str="lavender";   break;
      case 18: str="fawn";       break;
   }
   return str;                                                                               
}

string
randsize()
{
   string str;

   switch(random(5))
   {   

      case 0: str="satin";         break;
      case 1: str="velvet";        break;
      case 2: str="silk";          break;
      case 3: str="lace";          break;
      case 4: str="linen";         break;
   }
   return str;                                                                               
}

public mixed
wear(object ob)
{
    write("You wear the "+ short() +" over your shoulders, "+
        "leaving your midriff bare.\n");
    say(QCTNAME(this_player()) +" wears the "+ short() +" over " + 
        this_player()->query_possessive() +" shoulders. It clings "+
        "to "+ this_player()->query_objective() +" like a second "+
        "skin, emphasizing "+ this_player()->query_possessive() +
        " chest while leaving the midriff bare.\n");
    return 1;
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
 * Function name: init_recover
 * Description  : When the object recovers, this function is called to set
 *                the necessary variables. 
 * Arguments    : string argument - the arguments to parse
 */
public void
init_recover(string arg)
{
    string dummy;

    sscanf(arg, "%s#type#%s#%s", dummy, type, dummy);
    sscanf(arg, "%s#color#%s#%s", dummy, color, dummy);
    init_item_expiration_recover(arg);
    init_the_blouse();
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
    return MASTER + ":#type#" + type + "#color#" + color + "#"+ query_item_expiration_recover();
}


void
appraise_object(int num)
{
    ::appraise_object(num);
    appraise_wearable_item();
}
