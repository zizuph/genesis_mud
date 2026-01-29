/* 
 * Ice Cream Shop in Telseron
 * Coded by Cinderella
 * July 1996
 */
 
inherit "/std/room";
inherit "/lib/pub";
 
#include <stdproperties.h>
 
void
create_room()
{
    set_short("Ice cream shop");
    set_long("   This is the world famous ice cream shop of " +
        "Telseron. The ice creams are a favorite throughout all " +
        "of Emerald. They are delicious and are well enjoyed by " +
        "everyone. It has been rumoured that the even the Queen of " +
        "Telberin has a special order delivered to her on a weekly " +
        "basis. A large counter runs the length of the room. Under " +
        "the counter are glass cases which display the treats. A " +
        "plump jolly elf works here. He greets you warmly as he " +
        "waits on other who come to buy his tasty ice cream. You " +
        "see a menu painted on a plaque.\n");
 
    add_item("counter",
        "It is made of a solid piece of wood and polished. It " +
        "runs the length of the whole room.\n");
    add_item( ({"cases", "glass cases"}),
        "The glass cases are under the counter. Peering into " +
        "them, you see several bins of ice creams and sherberts " +
        "The cases are cold to the touch with ice crystals " +
        "forming around the edges of the cases.\n");
    add_item( ({"cases", "glass cases"}),
        "The floor is made of flagstones. It is swept clean " +
        "except for some crumbs that were missed in the corners.\n");
    add_item("plaque", 
        "Words have been inscribed into it.\n");
    add_cmd_item( "menu", "read", "@@menu_desc@@");
 
    add_food( "vanilla ice cream", "vanilla ice cream", 
        "soft", 50, 20, 
        "vanilla ice cream cone", 
        "vanilla ice cream cones",
        "You hold a cone of soft vanilla ice cream. It was just made " +
            "and looks absolutely delicious.\n");
    add_food( "chocolate ice cream", "chocolate ice cream", 
        "decadent", 50, 25, 
        "chocolate ice cream cone",
        "chocolate ice cream cones",
        "You hold a cone full of rich, delicious chocolate ice cream. " +
            "It has little chunks of chocolate in it and looks very " +
            "delicious.\n");
    add_food( "rainbow ice cream", "rainbow ice cream", 
        "smooth", 50, 35, 
        "rainbow ice cream cone",
        "rainbow ice cream cones",
        "This ice cream is made up of three delicious flavours:" +
           "vanilla, strawberry, and chocolate. This marvelous " +
           "combination is one of the elves favorite combinations and " +
           "is often sold out.\n");
    add_food( "rocky road ice cream", "rocky road ice cream", 
        "chunky", 70, 75,
        "rocky road ice cream cone", 
        "rocky road ice cream cones",
        "This flavour of ice cream is one of the elves favorites. It " +
            "has twice the chocolate flavour with miniature " +
            "marshallows and almond chunks mixed into it.\n");
    add_food( "ice cream boat", "ice cream boat",
        "large", 100, 100,
        "large ice cream boat",
        "large ice cream boats",
        "This novel ice cream dessert is made of two scoops of " +
        "chocolate and one scoop of soft vanilla ice cream. A secret " +
        "sauce has been spooned onto the ice cream. On either side " +
        "of the ice cream are bananas which have been cut. Whipped " +
        "cream has been spooned over the ice cream and bananas, nuts " +
        "have been sprinkled over all of it, and sweet cherries crown " +
        "each scoop of ice cream.\n");
    add_food( "orange sherbert", "orange sherbert",
        "fruity", 50, 35,
        "large bowl of orange sherbert",
        "large bowls of orange sherbert",
        "This fruity sherbert is made from orange juices. It is " +
            "tasty and sweet.\n");
    add_food( "peach sherbert", "peach sherbert",
        "sweet", 50, 45,
        "bowl of peach sherbert",
        "bowls of peach sherbert",
        "This bowl of peach sherbert is sweet and tasty. It " +
            "has little chunks of fresh peach in it.\n");
    add_food( "blueberry sherbert", "blueberry sherbert",
        "sweet", 50, 55,
        "bowl of blueberry sherbert",
        "bowls of blueberry sherbert",
        "This bowl full of blueberry sherbert is delicious. It " +
            "is made from fresh blueberries.\n");
    add_food( "strawberry sherbert", "strawberry sherbert",
        "smooth", 50, 60,
        "bowl of strawberry sherbert",
        "bowls of strawberry sherbert",
        "This bowl of strawberry sherbert is smooth and full " +
            "of flavorful strawberries. Nevertheless, there are no " +
            "seeds in it.\n");
    add_food( "raspberry sherbert", "raspberry sherbert",
        "creamy", 70, 70,
        "bowl of raspberry sherbert",
        "bowls of raspberry sherbert",
        "This bowl of raspberry sherbert is creamy and rich. Made " +
            "from fresh fruit today, it is tasty and very delicious.\n");
 
}
 
void
init()
{
   ::init();
   init_pub();
}
 
string
menu_desc()
{
   return "On the plaque, you see the following menu:\n\n" +
        "  Ice Creams\n" +
        "  ----------\n" +
        "  Vanilla. . . . . . . . . . . .   20 cc\n" +
        "  Chocolate. . . . . . . . . . .   25 cc\n" +
        "  Rainbow. . . . . . . . . . . .   35 cc\n" +
        "  Rocky road . . . . . . . . . .   75 cc\n" +
        "  Ice cream boat . . . . . . . .  100 cc\n\n" +
        "  Sherberts\n" +
        "  ---------\n" +
        "  Orange . . . . . . . . . . . .   35 cc\n" +
        "  Peach. . . . . . . . . . . . .   45 cc\n" +
        "  Blueberry. . . . . . . . . . .   55 cc\n" +
        "  Strawberry . . . . . . . . . .   60 cc\n" +
        "  Raspberry. . . . . . . . . . .   70 cc\n\n";
 
}
