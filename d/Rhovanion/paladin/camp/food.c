inherit "/std/food";
 
#include <macros.h>
#include <composite.h>
 
#define MAXFOOD 3
 
string *food_long=({"It just looks like piece of bread.\n",
                    "Usually looking apple.\n",
                    "You see nothing special in this herring.\n"});
string *food_short=({"piece of bread","apple","piece of herring"});
string *food_name=({"bread","apple","herring"});
 
void
create_food()
{
    int i;
    i=random(MAXFOOD);
    set_name(food_name[i]);
    set_long(food_long[i]);
    set_short(food_short[i]);
    set_amount(random(150)+50);
}
 
void
consume_text(object *arr, string vb)
{
    string str;
 
    write("You " + vb + " " + (str = COMPOSITE_DEAD(arr)) + ".\n");
    say(QCTNAME(this_player()) + " " + vb + "s " + str + ".\n");
}
