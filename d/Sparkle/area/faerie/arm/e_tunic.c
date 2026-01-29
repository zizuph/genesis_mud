/*
 * Tunic for elves in Faerie
 * - Finwe, August 2004
 */
inherit "/std/armour";

#include <macros.h>
#include <stdproperties.h>
#include <formulas.h>
#include <wa_types.h>

void
create_armour()
{
    int color_num, style_num, decor_num;
    string *color, *style, *decoration, decorated_text;

    color = ({"gold", "silver", "white", "yellow"});
    style = ({"plain", "decorated"});
    decoration = ({"leaves", "trees", "shapes" });

    color_num = random(sizeof(color));
    style_num = random(sizeof(style));
    decor_num = random(sizeof(decoration));
 
    set_name("tunic");
    set_pname("tunics");
    set_adj(color[color_num]);
    set_adj(style[style_num]);
    set_short(style[style_num] + " " + color[color_num] + " tunic");
    /*set_long("This is a " + short() + ". It extends to the knees, and " +
        "is woven from a light wool by elves. The cloth seems unusually " +
        "more durable than other fabrics." + decorated_text + "\n");
    */
        
    set_at(A_BODY);
    set_ac(10);
    set_am(({ -1, -1, 2 }));
    
    add_prop(OBJ_I_VALUE, 300);
    add_prop(OBJ_I_VOLUME, 4000);
    add_prop(OBJ_I_WEIGHT, 2500);

    switch(style_num)
    {
        case 0: // plain
        {
            decorated_text = "It is plain without any decorations.";
            break;
        }
        case 1: // styled
        {
            switch(decor_num)
            {
                case 0: // leaves
                {
                    add_item(({"leaves", "stylized leaves"}),
                        "They are large, artistic leaves sewn into " +
                        "the " + short() + ". The leaves cover the " +
                        "garment contrasting nicely with the cloth.\n");
                    decorated_text = "It is decorated with stylized leaves, " +
                        "which cover the garment in random patterns.";
                    break;
                }
                case 1:  // trees
                {
                    add_item(({"trees", "stylized trees"}),
                        "They are large and artistic representations " +
                        "of trees. The motifs are sewn into the " + 
                        short() + ". They contrast nicely with the cloth.\n");
                    decorated_text = "It is decorated with stylized " +
                        "trees, and cover the garment in random " +
                        "patterns and sizes.";
                    break;
                }
                case 2:  // shapes
                {
                    add_item(({"shapes", "random shapes"}),
                        "They are various sizes, and cover the " + 
                        short() + ". The shapes merge with the garment, " +
                        "almost offering some camoflauging to the wearer.\n");
                    decorated_text = "It is decorated with random shapes " +
                        "that cover the garment in random patterns.";
                    break;
                }
            }
            break;
        }
    }
    
    //set_long("This is a " + short() + ". It is a loose fitting garmet that goes down to the knees. The tunic is woven from a light wool by elves and seems unusually durable than other clothes. " + decorated_text + "\n");
    set_long("This is a " + short() + ". It extends to the knees, and " +
        "is woven from a light wool by elves. The cloth seems unusually " +
        "more durable than other fabrics. " + decorated_text + "\n");
    
}
