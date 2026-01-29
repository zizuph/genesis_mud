// -*-C++-*-
// file name: 	  /d/Avenir/common/bazaar/Obj/flower/flower_base.c
// creator(s):	  Lilith July 1997
// last update:	  
// purpose:       This is the base for flowers that can be delivered.
// note:      
// bug(s):
// to-do:

#include <flags.h>
#include <macros.h>
#include "/d/Avenir/include/defs.h"

int load;
string type, colour, size, message, deliver, target, from, her;

string radj();
string rnam();

public void set_type(string str)    {    type = str;      }
public void set_colour(string str)  {    colour = str;    }
public void set_message(string str) {    message = str;   }
public void set_target(string str)  {    target = str;    }
public void set_from(string str)    {    from = str;      }
public void set_load(int i)         {    load = i;        }
public void set_size(string str)    {    size = str;      }
public string query_type()          {    return type;     }
public string query_size()          {    return size;     }
public int query_load()             {    return load;     }

mapping flower_desc = ([
        "aster" : ({ "aster", "asters", "Asters grow on long stems "+
                     "with alternate, simple leaves. Each blossom "+
                     "contains a central disk of small, tubular "+
                     "petals surrounded by numerous showy, ray-like "+
                     "petals.", "It has a vague, undistinguished scent." }),
        "carnation" : ({ "carnation", "carnations", 
                     "Prized for their beauty, color, and fragrance, "+
                     "carnations have narrow opposite leaves and long, "+
                     "slightly branching stems that terminate in large, "+
                     "ruffled, double flowers.",
                     "It has a very pleasant, spicy fragrance." }), 
        "chrysanthemum" : ({ "chrysanthemum", "chrysanthemums", 
                     "Chrysanthemums have large showy blossoms which "+
                     "resemble very shaggy daisies. They are highly "+
                     "prized, ornamental flowers.", "It has a distinctive, "+
                     "though remarkably non-floral, scent." }),
        "daffodil" : ({ "daffodil", "daffodils", "Daffodils grow singly "+
                     "upon long, hollow, green stems. They have a funnel-"+
                     "shaped, ruffled crowns framed by several pointed, "+
                     "ovate petals.", "It has an unremarkable scent." }),
        "daisy" : ({ "daisy", "daisies", "Daisies have yellow centers "+
                     "and coloured outer petals. These flowers are small "+
                     "and cheerful, growing on sturdy stems.", "A very "+
                     "subtle, floral scent tantalizes your nose." }),
        "dragonflower" : ({ "dragonflower", "dragonflowers", "Also known "+
                     "as Dragon's-mouth, this dainty flower is a member "+
                     "of the orchid family. It vagely resembles the mouth "+
                     "of a dragon, with a deep-red throat and a long, "+
                     "protruding lip rimmed with a fringe of pale, white "+
                     "hairs.", "It has a very faint, but rather foul, odor." }),
        "forget-me-not" : ({ "forget-me-not", "forget-me-nots", 
                     "Forget-me-nots are tiny, delicate blossoms borne "+
                     "upon thin stalks. The yellow centers are surround"+
                     "ed by five tender petals which are delicately tint"+
                     "ed with colour.", "It has an unforgettable floral "+
                     "scent." }),
        "freesia" : ({ "freesia", "freesia", "Freesia are very elegant, "+
                     "arched rows of exquisitely scented flowers, prized "+
                     "for their beauty and longevity. The tubular flowers "+
                     "grow from delicate, spikelike racemes.", 
                     "The freesia has an incredibly lovely and unique "+
                     "fragrance, which you inhale deeply." }),
        "hibiscus" : ({ "hibiscus", "hibiscus", "Hibiscus flowers "+
                     "have long, yellow stamens protruding from the "+
                     "centers of their vividly coloured petals. It is "+
                     "an exotic and unusual flower, with a dark green "+
                     "stem and bushy, ovate leaves.", "It scent is "+
                     "unremarkable." }),              
        "honeysuckle" : ({ "honeysuckle", "honeysuckle", "Honey"+
                     "suckle's graceful, fragrant blossoms grow on a "+
                     "handsome, twining vine that bears broad, opposite "+
                     "leaves.", "It has a pleasantly sweet and very "+
                     "distinctive floral scent." }),
        "iris" : ({ "iris", "irises", "Iris is a colorful, orchidlike flower "+
                     "which has prominent gold tufts at the base of its "+
                     "petals. The linear, swordlike leaves, and small, "+
                     "showy flowers are symmetrical and, despite their "+
                     "elaborate appearance, relatively simple.", "You "+
                     "are unable to distinguish its scent." }),
        "lavender" : ({ "lavender", "lavender", "A member of the "+
                     "mint family, lavender is known for its delicate, "+
                     "fernlike leaves and small, delightfully fragrant "+
                     "flowers.", "What a lovely scent!" }),
        "lilac" : ({ "lilac", "lilacs", "Lilacs are harvested from "+
                     "bushes with simple, ovate leaves. The flowers grow "+
                     "in dense, pyramidal clusters of smaller blossoms, "+
                     "which have a heady, rich scent.", "It has a wonder"+
                     "fully strong, floral scent that is very distinctive." }),
        "lily" : ({ "lily", "lilies", "Lilies possess an elegant "+
                     "symmetry. The brilliantly hued flowers are tubular, "+
                     "with three petals and three sepals of similar appear"+
                     "ance. This one is striped and speckled, giving it a "+
                     "rather exotic appearance.", "It has a very delicate "+
                     "scent that reminds you of soap." }),    
        "orchid" : ({ "orchid", "orchids", "This orchid is also known "+
                     "as Fairy Slipper. It has a single leaf petiole and "+
                     "a single flower that is borne at the top of a bare "+
                     "stalk. The lip of the flower is large and pouchlike, "+
                     "resembling a slipper, while the sac is marked with "+
                     "purple and bears a patch of fine yellow hairs. It is"+
                     " a truly exquisite flower of inspirational beauty.",
                     "It has a very delicate, vaguely meaty smell." }),
        "passionflower" : ({"passionflower", "passionflowers",  
                     "This is an exotic-looking, highly "+
                     "aromatic flower. It has large three-lobed, "+
                     "serrated leaves with beautifully intricate flowers "+
                     "that are nearly as large as the palm of your hand. "+
                     "Its three stamens rise prominently above the twelve "+
                     "recurving petals and the colourful fringe surround"+
                     "ing them, the combination of which has created "+
                     "a unique flower instantly recognizable as passion"+
                     "flower.", "Its scent is sweet and intoxicating."}),
        "peony" : ({ "peony", "peonies", "The peony has spectacular, "+
                     "showy flowers of extraordinary hue.", "It has a "+
                     "strong, floral scent." }),
        "poppy" : ({ "poppy", "poppies", "This ornamental poppy has "+
                     "deeply dissected leaves and a long, slender stalk. "+
                     "Its large, showy flower vivid in hue, with an inner "+
                     "layer of velvety petals surrounding a black and "+
                     "yellow center. It is a very striking and unusual "+
                     "flower.", "It has an unremarkable scent." }),
        "rose" : ({ "rose", "roses", "Roses are prized for their "+
                     "rich colors, fragrance, and elegant forms. The "+
                     "flower itself is composed of five sepals and five "+
                     "petals that seem to glow with their own vibrant "+
                     "life. At the center of the petals, stamens are "+
                     "arranged in several concentric whorls. The thorns "+
                     "which normally grow upon the thick, dark green "+
                     "stem have been carefully removed.", "Such a glor"+
                     "ious scent, so heady as to be almost over-powering!" }),
        "tulip" : ({ "tulip", "tulips", "A small, delicate tulip of "+
                     "a variety that is found exclusively in Sybarus. "+
                     "This bell-shaped flower is borne on a single scape "+
                     "and is variegated in various shades of the same "+
                     "colour.", "I has a spicy, and vaguely sandalwood "+
                     "scent." })            
]);

mapping query_flower_map()
{
    return flower_desc;
}

string radj()
{
    string *randomadj;
    randomadj = ({"dark-eyed", "shy", "smiling", "delicate", 
                      "tiny", "sweet", "clean", "well-fed"});
    return randomadj[random(sizeof(randomadj))];
}

string rnam()
{
    string *randomname;
    randomname =  ({"child", "waif", "messenger", "urchin" });
    return randomname[random(sizeof(randomname))];
}

void
make_her()
{
    her = radj() +" "+ rnam();
}

string
query_her()
{
    return her;
}

public void
deliver()
{
    object t;
    string find_mess;

    t = find_player(target);

    if (!t || t->query_linkdead())
    {
         t = find_player(from); 
         find_mess = "I couldn't find "+ capitalize(target) +" anywhere!\n";
    }
    if (!find_mess)
        find_mess = "I have a special delivery for you from "+
                    capitalize(from) +"!\n";
    if (TO->move(t))
        TO->move(ENV(t));
    tell_object(t, "A "+ query_her() +" runs up to you and says: "+ 
        find_mess +"The "+ query_her() +" gives you a "+ 
        query_type() +".\n");
    tell_room(ENV(t), "A "+ query_her() +" runs up to "+ QCTNAME(t) +
         " and says: "+ find_mess +"The "+ query_her() +" gives "+   
         OBJECTIVE(t) +" a "+ query_type() +".\n", t);
    tell_room(ENV(t), "The "+ query_her() +" runs back home to Sybarus.\n");
}

public void
do_deliver()
{
    set_alarm(100.0, 0.0, "deliver");
} 

    