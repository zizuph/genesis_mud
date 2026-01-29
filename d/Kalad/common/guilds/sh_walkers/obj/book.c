inherit "/std/book";
#include "/d/Kalad/defs.h"
 
create_book()
{
    set_name("book");
    set_short("black leather-bound book");
    set_long("A book with hard, leather covered covers and a strong "+
    "hardened leather binding.\n");
    set_max_pages(2);
}

read_book_at_page(int page, string verb)
{
    if(page == 1)
    {
        write("A'right ye fools, I's gonna now tell ya how ye "+
    "make'a powerful weepon. I's only gonna tell ya once, so "+
    "pays attention! First'e'vol, ye gots ta get yerself a bottle. "+
    "Dats eazy, all ye do is grab one from the train'in room right "+
    "here. Den, ya needs some water. Just "+
    "fill up the bottle from the water basin right here."+
    " or yezs can get it from any place dat haz water. "+
    "Den, next "+
    "ya need is some horse crap. There is a stable somewhere off "+
    "in yon trade district above with a fat ol' horse. Just kick "+
    "that ol' horse in da ass, and a pice of crap should come out "+
    "and put it in yer bottle. Den, go down to the pub and get "+
    "yerself some alchohol. Don't even think of drinking it ya "+
    "pig-headed fool! Put in in yer bottle. "+
    "Remember that the more potent the alcohol, the more powerful "+
    "yer bomb will be. Now, ya need one more thing. This is where "+
    "it gets tricky. I have explored many different combos in my "+
    "life, and there are varying powers of the last ingredient, "+
    "depending on its substance. I find that if I gos down to the "+
    "ol' blacksmith on the cliffstreet and scrap up a bit of black "+
    "flakes from the anvil, I can use that rather well. Howevers, "+
    "I hear tell that some new substance they use on ships these "+
    "days works even better. And whats more, I hear that deep in "+
    "mountans, the dwarves mine fer some stuff that, if you can "+
    "find a way to crush, and add it to your mix, you can make "+
    "a wicked bomb! But even more faint, I hear that there is "+
    "a special item in a far off place, where you can get something "+
    "that packs more bang than you ever seen in yer life...ask me "+
    "about it some time. Anyways, \n");
    }
    if(page == 2)
    {
    write(    
    "now yer done! All ya doos now is got ta "+
    "'create explosive liquid', and ya mix up all yer ingredients "+
    "and if ya been paying attention to the instructer on alchemy, "+
    "and yer brain is bigger than a peanut, ya should come up with "+
    "a nice ol' bottle of boom water. Next, all ya need is a rag. "+
    "Ya can just pick that out of the rag bucket here, or if yer "+
    "in a hurry, you can rip a robe apart and use rags from it. "+
    "Now, yer done. Stuff it in, and yer bomb is complete! You can "+
    "throw it, or ye can hook it up to a trip wire. If ya want to "+
    "hook up a net to a trip wire, go down to the net store in the "+
    "port district. Don't use none of that flimsy fish net, use the "+
    "leather one. If you want to make a big dust cloud when someone "+
    "walks in, get yourself a sack or something, and then put some "+
    "dust in it. Ye can get yerself some dust right here from the "+
    "bucket. "+
    "Dats all ye dogs, get outs of my face.\n"+
    "Compiled by: \n"+
    "Takkahr the Jungle Thief,\n"+
    "Original speech by:\n"+
    "Regols, the Thief Trainer\n");
    }
}
