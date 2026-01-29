inherit "/d/Kalad/room_std";
inherit "/lib/pub";
#include "/d/Kalad/defs.h"
object brute;
object missy;
object shadar;

void
create_room()
{
   
   set_short("Inside Guido's Gaming Palace");
   set_long(
    "As you enter this room, you are greeted with the smell of smoke and\n"+   
    "sound of laughter and talking. All around the room you see packs of\n"+   
    "people crowded around gaming tables. The crowded bar is off to the\n"+    
    "the south, where the foul stench of alcohol and vomit is strong. There\n"+
    "is loud beautiful music being played by a band on a stage to the north.\n"+
    "The ceiling soars two stories high, with a balcony surrounding the\n"+   
    "sides of the room. Further down west, you see more of this giant and\n"+   
    "awesome casino.\n");
   add_item(({"bar"}),
    "The bar is packed with drunks, gamblers, merchants and prostitutes.\n"+
    "A fat black bearded bartender sits behind the bar, ordering his bar\n"+
    "maids around, who scramble around serving drinks. All around the bar,\n"+
    "there are spilt drinks laying about, as well as puddles of voimit,\n"+
    "probably left there by those who had just a little too much. The foul\n"+
    "stench is sickening, but you soon get used to it, just like everyone\n"+
    "else seems to do. There is a menu behind the bar.\n");
   add_cmd_item("menu","read","@@menu");
   add_item(({"gaming tables","tables"}),
    "They are scattered around the room, with packs of people around them.\n"+
    "There seems to be some that are open further down to the west.\n");
   add_item(({"people"}),
    "There are all sorts of people here. Mostly human, but you do see the\n"+
    "occasional goblin, hobbit, elf and dwarf. Apparently the only people\n"+
    "they discriminate againts are those without cash.\n");
   add_item(({"stage"}),
    "A large stage with a band playing on it.\n");
   add_item(({"band"}),
    "This band, consisting of three young woman, is lost in their music.\n"+
    "They seem to be playing a sort of spanish/moorish song, which sounds\n"+
    "very pleasent.\n");
   add_item(({"woman"}),
    "Three very beautiful and young woman. One, dark-haired, dark-eyed\n"+
    "beauty is singing with a angel voice. Another, blond haired, dark-eyed\n"+
    "woman is skillfuly playing the guitar, while the third and most lovely\n"+
    "looking green-eyed red haired girl is playing a tabla.\n");
   add_item(({"balcony"}),
    "The balcony surrounds the entire room, and you can see stairs down to\n"+
    "west that lead up to it. There are two levels of balconies, as there\n"+
    "are 3 levels to this casino. You see a couple of wanton, scantly-clad\n"+
    "woman leaning over the railing smiling and winking at you.\n");
   set_alarm(1.0, 0.0, "reset_room");
   add_prop(MRKT_IN_NO_HEAR,1);
   add_item(({"vomit"}),"Yuck.\n");
   add_exit(MRKT_PATH(casino02), "west");
   add_exit(MRKT_PATH(m19), "east");
   add_drink(({"revolain ale",
   "ale","ales"}),"ale","revolian",5,50,12,0,0,"A refreshing brew.\n",0);
   add_drink(({"red revolain ale","red ale","red ales"}),"ale","red revolian",
   10,50,24,0,0,"A refreshing brew made of strage red liquid that seems to"+
   " bubble slightly.\n",0); 
   add_drink(({"wine","spiced wine","wines"}),"wine","spiced",15,100,50,0,0,
   "A wine with an ancient and herbal scent.\n",0);
   add_drink(({"mead","yellow mead","meads"}),"mead","yellow",30,200,100,0,0,
   "A very strong brew that has a strange yellowish tint to it.\n",0);
   add_drink(({"black mead","black meads"}),"mead","black",40,200,120,0,0,
   "A powerful brew colored black. The mere oder of it makes you dizzy.\n",0);
} 

string
menu()
{
    return
    "######################################\n"+
    "#         Guido's Pub Drinks         #\n"+
    "#------------------------------------#\n"+
    "# Revolian Ale       -      12 cc    #\n"+
    "# Red Revolian Ale   -      24 cc    #\n"+
    "# Spiced Wine        -      50 cc    #\n"+
    "# Yellow Mead        -     100 cc    #\n"+
    "# Black Mead         -     120 cc    #\n"+
    "######################################\n";
} 
reset_room()
{
    if(!missy)
    {
       missy = clone_object("/d/Kalad/common/market/npc/missy");
       missy -> move_living("arrives",TO);
    }
    if(!brute)
    {
       brute = clone_object("/d/Kalad/common/market/npc/meanb");
       brute -> move_living("arrives.",TO);
    }
    if(!shadar)
    {
        shadar = clone_object("/d/Kalad/common/market/npc/shark");
        shadar -> move_living("arrives",TO);
    }
}
void
init()
{
    ::init();
    init_pub();
}
