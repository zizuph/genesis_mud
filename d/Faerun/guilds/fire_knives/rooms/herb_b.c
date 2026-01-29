/*
 * /d/Gondor/morgul/cellar/herb_base.c
 *
 *  Herb Shop
 *
 *  Standard herb shop for Gondor
 *  Copied from Minas Morgul herb shop
 *
 *  Olorin, 15-nov-1994
 *
 *  Modification Log:
 *  October 13, 2003 -- added herbal wraps. Serif.
 *  August  24, 2004, Raven: added heap support in query_sell_price(object).
 *
 *  Re-ediditng began 2006-10-18 by Toby since a mishap with the new changes.
 *                    2006-10-22, Toby: Added functionality to list via category
 *                                      for Mages i.e. list herbs leaves
 *                    2006-10-23, Toby: Completed the re-coding of the domain 
 *                                      listing of herbs. 
 *                    2006-11-17, Toby: Changed how coinage is displayed (finally)
 *                    2006-11-19, Toby: Implemented support for appointing a 
 *                                      Herbalist in the Society 'list focus herbs'
 *                                      The herbs are set in the herb_shop
 *                    2009-08-23, Eowul: Added activity for selling special mage
 *                                       herbs.
 *                    2017-08-11, Finwe: Commented out herb wraps. They became 
                                         obsolete years ago. Updated sprintf to
                                         add commas to large numbers.
 */
#pragma save_binary
#pragma strict_types

#include "/d/Faerun/defs.h"
#include "../guild.h";
 
inherit "/lib/shop.c";
inherit FIREKNIVES_STD_ROOM;

#include <cmdparse.h>
#include <composite.h>
#include <files.h>
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/common/guild2/lib/morgul_herbs.h"

#define FIREKNIVES_HERBALIST_MASTER  "/d/Faerun/guilds/fire_knives/rooms/herb"

string  read_sign();
public string money_text(int am);

/* Definitions for the listing of herbs. */
#define IS_HERB_ME(ob)        ( (extract(ob, 0, 8) == "/d/Gondor") || (extract(ob, 0, 7) == "/d/Shire") )
#define IS_HERB_AVENIR(ob)    ( extract(ob, 0, 8) == "/d/Avenir" )
#define IS_HERB_CALIA(ob)     ( extract(ob, 0, 7) == "/d/Calia" )
#define IS_HERB_EARTHSEA(ob)  ( extract(ob, 0,10) == "/d/Earthsea" )
#define IS_HERB_EMERALD(ob)   ( extract(ob, 0, 9) == "/d/Emerald" )
#define IS_HERB_FAERUN(ob)    ( extract(ob, 0, 8) == "/d/Faerun" )
#define IS_HERB_KALAD(ob)     ( extract(ob, 0, 7) == "/d/Kalad" )
#define IS_HERB_KHALAKHOR(ob) ( extract(ob, 0,11) == "/d/Khalakhor" )
#define IS_HERB_KRYNN(ob)     ( extract(ob, 0, 7) == "/d/Krynn" )
#define IS_HERB_SPARKLE(ob)   ( extract(ob, 0, 9) == "/d/Sparkle" )
#define IS_HERB_TEREL(ob)     ( extract(ob, 0, 7) == "/d/Terel" )


#define NUM                   sizeof(MONEY_TYPES)
#define COIN_TYPES            ({ "cc", "sc", "gc", "pc" })

void
init_herb_shop()
{
    add_action("do_smell", "smell");
    init_shop();
}

string
read_sign()
{
    return "\t __________________________________________\n" +
    "\t|                                          |\n" +
    "\t|            H E R B   S H O P             |\n" +
    "\t|            =================             |\n" +
    "\t|                                          |\n" +
    "\t|   Herbs from near and distant areas are  |\n" +
    "\t|   for sale here. We also buy herbs and   |\n" +
    "\t|   store them properly for later use for  |\n" +
    "\t|   Broterhood members.                    |\n" +
    "\t|                                          |\n" +
    "\t|    'List herbs/all herbs [category]'     |\n" +
    "\t|__________________________________________|\n";
}

int
do_read(string str)
{
    return 0;
}

/*    
 * Function name: query_buy_price
 * Description:   What price should the player pay
 * Arguments:     ob - The object to test
 * Returns:       The price
 */
int
query_buy_price(object ob)
{
    int seed;

    sscanf(OB_NUM(ob), "%d", seed);

    return 2 * ob->query_herb_value() * (query_money_greed_buy() +
        15 - this_player()->query_skill(SS_TRADING) / 4 +
        random(15, seed)) / 100;
}

int
query_buy_price_special(object ob)
{
    int seed;

    sscanf(OB_NUM(ob), "%d", seed);

    return 2 * ob->query_prop(OBJ_I_VALUE) * (query_money_greed_buy() +
        15 - this_player()->query_skill(SS_TRADING) / 4 +
        random(15, seed)) / 100;
}

/*    
 * Function name: query_sell_price
 * Description:   What price will the player get when selling an object?
 * Arguments:     ob - The object
 * Returns:   The price
 */
int
query_sell_price(object ob)
{
    int seed;

    sscanf(OB_NUM(ob), "%d", seed);

    return (ob->num_heap() || 1) * ob->query_herb_value() * 100 /
        (query_money_greed_sell() +
        15 - this_player()->query_skill(SS_TRADING) / 3 + 
        random(15, seed + 1)); /* Use another seed than on buying */
}

int
shop_hook_allow_sell(object ob)  /*If not an herb, don't take it*/
{
    return IS_HERB_OBJECT(ob);
}

int
herb_filter(object ob)
{
    return IS_HERB_OBJECT(ob);
}

/*
 * Function name: shop_hook_list_empty_store
 * Description  : If the storeroom is empty when the player wants a list
 *                of its items
 * Arguments    : str - If player specified string
 */
void
shop_hook_list_empty_store( string str )
{
    notify_fail( "There are currently no herbs of the requested type "+
        "for sale.\n" );
}

/*
 * Function name: shop_hook_list_other
 * Description:   List an object other than a herb
 * Arguments:     ob - The object
 */
void
shop_hook_list_other(object ob, int price)
{
    string str, mess;

    str = sprintf("        %-29s - ", capitalize(ob->short()));

    if (mess = text(split_values(price)))
        write(str + mess + ".\n");
    else
        write(str + "That item wouldn't cost you much.\n");
}

/*
 * Function name: query_shop_hook_restricted_herb
 * Description: Test if this player may buy this particular herb.
 * Arguments: pl - this_player(), str - the herb name.
 */
int
query_shop_hook_restricted_herb(object pl, string str)
{
    return 0;
}

int filter_herbs(string ob, string domain)
{
   if(domain == "me")
      return (IS_HERB_ME(ob));
   else if(domain == "avenir")
      return (IS_HERB_AVENIR(ob));
   else if(domain == "calia")
      return (IS_HERB_CALIA(ob));
   else if(domain == "earthsea")
      return (IS_HERB_EARTHSEA(ob));
   else if(domain == "emerald")
      return (IS_HERB_EMERALD(ob));
   else if(domain == "faerun")
      return (IS_HERB_FAERUN(ob));
   else if(domain == "kalad")
      return (IS_HERB_KALAD(ob));
   else if(domain == "khalakhor")
      return (IS_HERB_KHALAKHOR(ob));
   else if(domain == "krynn")
      return (IS_HERB_KRYNN(ob));
   else if(domain == "sparkle")
      return (IS_HERB_SPARKLE(ob));
   else if(domain == "terel")
      return (IS_HERB_TEREL(ob));

}

/*
 * Function name: money_text
 * Description:   convert a price in cc into a formatted
 *                string, giving the price using the smallest
 *                number of coins
 * Arguments:     am - the price in cc
 * Returns:       the string, eg: 1 pc  2 gc 10 sc  9 cc
 */
public string
money_text(int am)
{
    int    *arr = MONEY_SPLIT(am),
            ind = NUM;
    string  txt = "";

    while (--ind >= 0)
    {
        if (arr[ind])
            txt += sprintf("%2d %2s ", arr[ind], COIN_TYPES[ind]);
        else
            txt += "      ";
    }

    return txt;
}


/*
 * Function name:   do_list
 * Description:     Provide a list of herbs in the store room
 * Arguments:       str - what are we trying to list.
 *                  Examples: list wares, list all herbs, list blue leaves
 * Returns:         0 if not recognised
 *                  1 otherwise
 */
int
do_list( string str )
{
    int     i, j, price, iCategoryList = 0;
    mapping herbs,
            herb_names = ([]),
            herb_names_me = ([]),
            herb_names_avenir = ([]),
            herb_names_calia = ([]),
            herb_names_earthsea = ([]),
            herb_names_emerald = ([]),
            herb_names_faerun = ([]),
            herb_names_kalad = ([]),
            herb_names_khalakhor = ([]),
            herb_names_krynn = ([]),
            herb_names_sparkle = ([]),
            herb_names_terel = ([]);

    object  herb, *herb_objects = ({});
    string  Ts1, Ts2, sCategory;
    string  *herb_files, 
            *herb_files_me,
            *herb_files_avenir,
            *herb_files_calia,
            *herb_files_earthsea,
            *herb_files_emerald,
            *herb_files_faerun,
            *herb_files_kalad,
            *herb_files_khalakhor,
            *herb_files_krynn,
            *herb_files_sparkle,
            *herb_files_terel;

    mapping herbs_focus = ([]);
    string  *focus_list, note_str;
    object  herb_note;

    if (str == "spells")
    {
        return 0;
    }


    if (strlen( str ) == 0)
    {
        if (FIREKNIVES_MASTER->is_occ_fireknife(this_player()->query_name()) == 1 
        || this_player()->query_wiz_level())
        {
            write( "You can the following commands:\n" +
                   "   - List herbs/all herbs [category]\n");
                   
           
        }
       
        return 1;
    }
    
    else if (parse_command(str, ({ }), " [all] 'herbs' %s", sCategory))
    {
        setuid();
        seteuid( getuid() );

        herbs = store_room->query_herbs();
        herb_files = m_indexes( herbs );

        j = sizeof( herb_files );

        if(stringp(sCategory) && (strlen(sCategory) > 3) && 
           (FIREKNIVES_MASTER->is_occ_fireknife(this_player()->query_name()) == 1 
           || this_player()->query_wiz_level()))
        {
           /* This section handles the filtering of herbs through a category.
            * The list is passed on to regular printing later in the file.
            */
           for (i=0;i < j;i++)
           {                     /*We merely load a herb here. It's a double
                                  *check. We check whether it has loaded and
                                  *whether it has at least a valid name.  */
               if (strlen( herb_files[i]->query_herb_name() ) != 0)
               {
                   herb_objects += ({ find_object( herb_files[i] ) });
               }
           }
                                /*Here we filter our herbs.               */
           if (!parse_command( sCategory, herb_objects, "%i", herb_objects ))
           {
               write( "We have no herbs of this type.\n" );
               return 1;
           }
           
           iCategoryList = 1;

           j = sizeof( herb_objects );
  
           herb_objects = herb_objects[1..j];
                                /*Now once filtered, let us create
                                 *the apropriate shop list entries.       */
           j--;
           for (i=0; i < j;i++)
           {
               Ts1 = herb_objects[i]->query_herb_name();
               Ts1 += " ";
               Ts2 = money_text( query_buy_price( herb_objects[i] ) );

               if (!Ts2)
               {
                   Ts2 = "That herb wouldn't cost you much";
               }

               herb_names += ([ Ts1 : sprintf( "\t%,6d %-'.'34s ",
                   herbs[file_name(herb_objects[i])], capitalize(Ts1) ) + Ts2+"\n" ]);
           }
        }
        else
        {
           /* This section handles the filtering of herbs per domain.
            * The lists is printed after this section.
            *
            * Perhaps I could code some sort of loop to update all
            * the separated lists, but for now it will be manually
            * to get the shop up and running again. (Toby, 2006-10-23)
            */
           herb_files_me = filter(herb_files, &filter_herbs(, "me"));
           herb_files -= herb_files_me;
           herb_files_avenir = filter(herb_files, &filter_herbs(, "avenir"));
           herb_files -= herb_files_avenir;
           herb_files_calia = filter(herb_files, &filter_herbs(, "calia"));
           herb_files -= herb_files_calia;
           herb_files_earthsea = filter(herb_files, &filter_herbs(, "earthsea"));
           herb_files -= herb_files_earthsea;
           herb_files_emerald = filter(herb_files, &filter_herbs(, "emerald"));
           herb_files -= herb_files_emerald;
           herb_files_faerun = filter(herb_files, &filter_herbs(, "faerun"));
           herb_files -= herb_files_faerun;
           herb_files_kalad = filter(herb_files, &filter_herbs(, "kalad"));
           herb_files -= herb_files_kalad;
           herb_files_khalakhor = filter(herb_files, &filter_herbs(, "khalakhor"));
           herb_files -= herb_files_khalakhor;
           herb_files_krynn = filter(herb_files, &filter_herbs(, "krynn"));
           herb_files -= herb_files_krynn;
           herb_files_sparkle = filter(herb_files, &filter_herbs(, "sparkle"));
           herb_files -= herb_files_sparkle;
           herb_files_terel = filter(herb_files, &filter_herbs(, "terel"));
           herb_files -= herb_files_terel;
           
           // ===== MIDDLE EARTH SORTING =====
           j = sizeof( herb_files_me );
           for (i=0;i < j;i++)
           {
               if (strlen( Ts1 = herb_files_me[i]->query_herb_name() ) != 0)
               {
                   herb = find_object( herb_files_me[i] );
                   Ts1 += " ";
                   Ts2 = money_text( query_buy_price( herb ) );
 
                   if (!Ts2)
                   {
                       Ts2 = "That herb wouldn't cost you much";
                   }
        
                   herb_names_me += ([ Ts1 : sprintf( "\t%,6d %-'.'34s ",
                       herbs[herb_files_me[i]], capitalize(Ts1) ) + Ts2+"\n" ]);
               }
           }

           // ===== AVENIR SORTING =====
           j = sizeof( herb_files_avenir );
           for (i=0;i < j;i++)
           {
               if (strlen( Ts1 = herb_files_avenir[i]->query_herb_name() ) != 0)
               {
                   herb = find_object( herb_files_avenir[i] );
                   Ts1 += " ";
                   Ts2 = money_text( query_buy_price( herb ) );
 
                   if (!Ts2)
                   {
                       Ts2 = "That herb wouldn't cost you much";
                   }
        
                   herb_names_avenir += ([ Ts1 : sprintf( "\t%,6d %-'.'34s ",
                       herbs[herb_files_avenir[i]], capitalize(Ts1) ) + Ts2+"\n" ]);
               }
           }

           // ===== CALIA SORTING =====
           j = sizeof( herb_files_calia );
           for (i=0;i < j;i++)
           {
               if (strlen( Ts1 = herb_files_calia[i]->query_herb_name() ) != 0)
               {
                   herb = find_object( herb_files_calia[i] );
                   Ts1 += " ";
                   Ts2 = money_text( query_buy_price( herb ) );
 
                   if (!Ts2)
                   {
                       Ts2 = "That herb wouldn't cost you much";
                   }
        
                   herb_names_calia += ([ Ts1 : sprintf( "\t%,6d %-'.'34s ",
                       herbs[herb_files_calia[i]], capitalize(Ts1) ) + Ts2+"\n" ]);
               }
           }
           // ===== EARTHSEA SORTING =====
           j = sizeof( herb_files_earthsea );
           for (i=0;i < j;i++)
           {
               if (strlen( Ts1 = herb_files_earthsea[i]->query_herb_name() ) != 0)
               {
                   herb = find_object( herb_files_earthsea[i] );
                   Ts1 += " ";
                   Ts2 = money_text( query_buy_price( herb ) );
 
                   if (!Ts2)
                   {
                       Ts2 = "That herb wouldn't cost you much";
                   }
        
                   herb_names_earthsea += ([ Ts1 : sprintf( "\t%,6d %-'.'34s ",
                       herbs[herb_files_earthsea[i]], capitalize(Ts1) ) + Ts2+"\n" ]);
               }
           }
           // ===== EARTHSEA SORTING =====
           j = sizeof( herb_files_earthsea );
           for (i=0;i < j;i++)
           {
               if (strlen( Ts1 = herb_files_earthsea[i]->query_herb_name() ) != 0)
               {
                   herb = find_object( herb_files_earthsea[i] );
                   Ts1 += " ";
                   Ts2 = money_text( query_buy_price( herb ) );
 
                   if (!Ts2)
                   {
                       Ts2 = "That herb wouldn't cost you much";
                   }
        
                   herb_names_earthsea += ([ Ts1 : sprintf( "\t%,6d %-'.'34s ",
                       herbs[herb_files_earthsea[i]], capitalize(Ts1) ) + Ts2+"\n" ]);
               }
           }
           // ===== EMERALD SORTING =====
           j = sizeof( herb_files_emerald );
           for (i=0;i < j;i++)
           {
               if (strlen( Ts1 = herb_files_emerald[i]->query_herb_name() ) != 0)
               {
                   herb = find_object( herb_files_emerald[i] );
                   Ts1 += " ";
                   Ts2 = money_text( query_buy_price( herb ) );
 
                   if (!Ts2)
                   {
                       Ts2 = "That herb wouldn't cost you much";
                   }
        
                   herb_names_emerald += ([ Ts1 : sprintf( "\t%,6d %-'.'34s ",
                       herbs[herb_files_emerald[i]], capitalize(Ts1) ) + Ts2+"\n" ]);
               }
           }

           // ===== FAERUN SORTING =====
           j = sizeof( herb_files_faerun );
           for (i=0;i < j;i++)
           {
               if (strlen( Ts1 = herb_files_faerun[i]->query_herb_name() ) != 0)
               {
                   herb = find_object( herb_files_faerun[i] );
                   Ts1 += " ";
                   Ts2 = money_text( query_buy_price( herb ) );
 
                   if (!Ts2)
                   {
                       Ts2 = "That herb wouldn't cost you much";
                   }
        
                   herb_names_faerun += ([ Ts1 : sprintf( "\t%,6d %-'.'34s ",
                       herbs[herb_files_faerun[i]], capitalize(Ts1) ) + Ts2+"\n" ]);
               }
           }

           // ===== KALAD SORTING =====
           j = sizeof( herb_files_kalad );
           for (i=0;i < j;i++)
           {
               if (strlen( Ts1 = herb_files_kalad[i]->query_herb_name() ) != 0)
               {
                   herb = find_object( herb_files_kalad[i] );
                   Ts1 += " ";
                   Ts2 = money_text( query_buy_price( herb ) );
 
                   if (!Ts2)
                   {
                       Ts2 = "That herb wouldn't cost you much";
                   }
        
                   herb_names_kalad += ([ Ts1 : sprintf( "\t%,6d %-'.'34s ",
                       herbs[herb_files_kalad[i]], capitalize(Ts1) ) + Ts2+"\n" ]);
               }
           }

           // ===== KHALAKHOR SORTING =====
           j = sizeof( herb_files_khalakhor );
           for (i=0;i < j;i++)
           {
               if (strlen( Ts1 = herb_files_khalakhor[i]->query_herb_name() ) != 0)
               {
                   herb = find_object( herb_files_khalakhor[i] );
                   Ts1 += " ";
                   Ts2 = money_text( query_buy_price( herb ) );
 
                   if (!Ts2)
                   {
                       Ts2 = "That herb wouldn't cost you much";
                   }
        
                   herb_names_khalakhor += ([ Ts1 : sprintf( "\t%,6d %-'.'34s ",
                       herbs[herb_files_khalakhor[i]], capitalize(Ts1) ) + Ts2+"\n" ]);
               }
           }

           // ===== KRYNN SORTING =====
           j = sizeof( herb_files_krynn );
           for (i=0;i < j;i++)
           {
               if (strlen( Ts1 = herb_files_krynn[i]->query_herb_name() ) != 0)
               {
                   herb = find_object( herb_files_krynn[i] );
                   Ts1 += " ";
                   Ts2 = money_text( query_buy_price( herb ) );
 
                   if (!Ts2)
                   {
                       Ts2 = "That herb wouldn't cost you much";
                   }
        
                   herb_names_krynn += ([ Ts1 : sprintf( "\t%,6d %-'.'34s ",
                       herbs[herb_files_krynn[i]], capitalize(Ts1) ) + Ts2+"\n" ]);
               }
           }

           // ===== SPARKLE SORTING =====
           j = sizeof( herb_files_sparkle );
           for (i=0;i < j;i++)
           {
               if (strlen( Ts1 = herb_files_sparkle[i]->query_herb_name() ) != 0)
               {
                   herb = find_object( herb_files_sparkle[i] );
                   Ts1 += " ";
                   Ts2 = money_text( query_buy_price( herb ) );
 
                   if (!Ts2)
                   {
                       Ts2 = "That herb wouldn't cost you much";
                   }
        
                   herb_names_sparkle += ([ Ts1 : sprintf( "\t%,6d %-'.'34s ",
                       herbs[herb_files_sparkle[i]], capitalize(Ts1) ) + Ts2+"\n" ]);
               }
           }

           // ===== TEREL SORTING =====
           j = sizeof( herb_files_terel );
           for (i=0;i < j;i++)
           {
               if (strlen( Ts1 = herb_files_terel[i]->query_herb_name() ) != 0)
               {
                   herb = find_object( herb_files_terel[i] );
                   Ts1 += " ";
                   Ts2 = money_text( query_buy_price( herb ) );
 
                   if (!Ts2)
                   {
                       Ts2 = "That herb wouldn't cost you much";
                   }
        
                   herb_names_terel += ([ Ts1 : sprintf( "\t%,6d %-'.'34s ",
                       herbs[herb_files_terel[i]], capitalize(Ts1) ) + Ts2+"\n" ]);
               }
           }

           // ===== SORTING THE REST =====
           j = sizeof( herb_files );

           for (i=0;i < j;i++)
           {
               if (strlen( Ts1 = herb_files[i]->query_herb_name() ) != 0)
               {
                   herb = find_object( herb_files[i] );
                   Ts1 += " ";
                   Ts2 = money_text( query_buy_price( herb ) );
 
                   if (!Ts2)
                   {
                       Ts2 = "That herb wouldn't cost you much";
                   }
        
                   herb_names += ([ Ts1 : sprintf( "\t%,6d %-'.'34s ",
                       herbs[herb_files[i]], capitalize(Ts1) ) + Ts2+"\n" ]);
               }
           }
        }
    }
    else
    {
        write ("List what? List [herbs/all herbs]\n");
        return 1;
    }
                                /*We use the old variable to store herbs'
                                 *names this time.                        */
    herb_files = m_indexes( herb_names );
    herb_files_me = m_indexes( herb_names_me );
    herb_files_avenir = m_indexes( herb_names_avenir );
    herb_files_calia = m_indexes( herb_names_calia );
    herb_files_earthsea = m_indexes( herb_names_earthsea );
    herb_files_emerald = m_indexes( herb_names_emerald );
    herb_files_faerun = m_indexes( herb_names_faerun );
    herb_files_kalad = m_indexes( herb_names_kalad );
    herb_files_khalakhor = m_indexes( herb_names_khalakhor );
    herb_files_krynn = m_indexes( herb_names_krynn );
    herb_files_sparkle = m_indexes( herb_names_sparkle );
    herb_files_terel = m_indexes( herb_names_terel );

                                /*Let's sort it too. Note, that taking
                                 *m_values() we lose sorting. That's why it
                                 *can't be done in a more efficient way.  */
    herb_files = sort_array( herb_files );
    herb_files_me = sort_array( herb_files_me );
    herb_files_avenir = sort_array( herb_files_avenir );
    herb_files_calia = sort_array( herb_files_calia );
    herb_files_earthsea = sort_array( herb_files_earthsea );
    herb_files_emerald = sort_array( herb_files_emerald );
    herb_files_faerun = sort_array( herb_files_faerun );
    herb_files_kalad = sort_array( herb_files_kalad );
    herb_files_khalakhor = sort_array( herb_files_khalakhor );
    herb_files_krynn = sort_array( herb_files_krynn );
    herb_files_sparkle = sort_array( herb_files_sparkle );
    herb_files_terel = sort_array( herb_files_terel );

    write( "   ========\\\\ We sell the following herbs of the requested type: //==="+
        "======\n\n" );
/* 
 *  if(iCategoryList)
 *     Print herbs of one type 'moss/berry(berries/etc'
 *  else
 *     Print herbs with domain as index
 *
 */
    if(iCategoryList)
    {
       j = sizeof( herb_files );

       if (j == 0)
           shop_hook_list_empty_store( str );

       for (i=0;i < j;i++)
           write( herb_names[herb_files[i]] );
    }
    else
    {
       write("        ==============\\\\     Herbs of Middle Earth     //==============\n\n");

       j = sizeof( herb_files_me );

       if (j == 0)
           shop_hook_list_empty_store( str );

       for (i=0;i < j;i++)
           write( herb_names_me[herb_files_me[i]] );

       write("\n        ==============\\\\        Herbs of Avenir        //==============\n\n");
  
       j = sizeof( herb_files_avenir );

       if (j == 0)
           shop_hook_list_empty_store( str );

       for (i=0;i < j;i++)
           write( herb_names_avenir[herb_files_avenir[i]] );

       write("\n        ==============\\\\        Herbs of Calia         //==============\n\n");

       j = sizeof( herb_files_calia );

       if (j == 0)
           shop_hook_list_empty_store( str );

       for (i=0;i < j;i++)
           write( herb_names_calia[herb_files_calia[i]] );

       write("\n        ==============\\\\      Herbs of Earthsea      //==============\n\n");
  
       j = sizeof( herb_files_earthsea );

       if (j == 0)
           shop_hook_list_empty_store( str );

       for (i=0;i < j;i++)
           write( herb_names_earthsea[herb_files_earthsea[i]] );

       write("\n        ==============\\\\      Herbs of Emerald      //==============\n\n");
  
       j = sizeof( herb_files_emerald );

       if (j == 0)
           shop_hook_list_empty_store( str );

       for (i=0;i < j;i++)
           write( herb_names_emerald[herb_files_emerald[i]] );

       write("\n        ==============\\\\        Herbs of Faerun        //==============\n\n");
  
       j = sizeof( herb_files_faerun );

       if (j == 0)
           shop_hook_list_empty_store( str );

       for (i=0;i < j;i++)
           write( herb_names_faerun[herb_files_faerun[i]] );

       write("\n        ==============\\\\        Herbs of Kalad         //==============\n\n");

       j = sizeof( herb_files_kalad );

       if (j == 0)
           shop_hook_list_empty_store( str );

       for (i=0;i < j;i++)
           write( herb_names_kalad[herb_files_kalad[i]] );

       write("\n        ==============\\\\       Herbs of Khalakhor      //==============\n\n");
  
       j = sizeof( herb_files_khalakhor );

       if (j == 0)
           shop_hook_list_empty_store( str );

       for (i=0;i < j;i++)
           write( herb_names_khalakhor[herb_files_khalakhor[i]] );

       write("\n        ==============\\\\        Herbs of Krynn         //==============\n\n");

       j = sizeof( herb_files_krynn );

       if (j == 0)
           shop_hook_list_empty_store( str );

       for (i=0;i < j;i++)
           write( herb_names_krynn[herb_files_krynn[i]] );

       write("\n        ==============\\\\        Herbs of Sparkle       //==============\n\n");
  
       j = sizeof( herb_files_sparkle );

       if (j == 0)
           shop_hook_list_empty_store( str );

       for (i=0;i < j;i++)
           write( herb_names_sparkle[herb_files_sparkle[i]] );

       write("\n        ==============\\\\        Herbs of Terel         //==============\n\n");

       j = sizeof( herb_files_terel );

       if (j == 0)
           shop_hook_list_empty_store( str );

       for (i=0;i < j;i++)
           write( herb_names_terel[herb_files_terel[i]] );

       write("\n        ==============\\\\    Herbs of unknown origin    //==============\n\n");

       j = sizeof( herb_files );

       if (j == 0)
           shop_hook_list_empty_store( str );

       for (i=0;i < j;i++)
       {
           write( herb_names[herb_files[i]] );
       }
    }

    write( "\n   \\\\======================================================="+
           "==============//\n");

    return 1;
}

static int
filter_herb_name(string herb_file, string name)
{
    if (file_size(herb_file + ".c") > 0)
        return (herb_file->query_herb_name() == name);

    return 0;
}

int
query_shop_no_business(mixed pl)
{
    return 0;
}

void
shop_hook_no_business(object pl)
{
    NF("");
    tell_room(this_object(), "The herbalist says: I do not want your business, " +
      (pl->query_gender() ? "Lady" : "Mister") + "!\n");
    write("The herbalist spits at you.\n");
    say("The herbalist spits at " + QTNAME(pl) + ".\n");
    tell_room(TO, "The herbalist says: Leave before I call the guards!\n");
}

int
shop_hook_restricted_herb(object pl, string str)
{
    notify_fail("That particular herb is restricted from sale.\n");
}

/*
 * Function name: do_buy
 * Description:   Try to let the player buy a herb
 * Arguments:     string - describing how to pay and get change
 * Returns:       1 on sucess
 */
int
do_buy(string str)
{
    int     i, j,
            number = 0,
            max_num;
    object *item = ({}),
           *bought_item,
            store;
    string  str1,
            str2,
            str3,
           *herb_files;
    mapping herbs;

    if (query_shop_no_business(this_player()))
    {
        shop_hook_no_business(this_player());
        return 0;
    }

    if (!str || str =="")
    {
        notify_fail("Buy what?\n");
        return 0;
    }

    call_other(store_room, "load_me"); /* Make sure storeroom is loaded */

    /*  Did the player specify payment and change? */
    if ((sscanf(str,"%d %s for %s and get %s", number, str1, str2, str3) != 4) &&
        (sscanf(str, "%s for %s and get %s", str1, str2, str3) != 3))
    {
    /* Well, maybe player has defined how payment will be done atleast? */
        str3 = "";

        if ((sscanf(str,"%d %s for %s", number, str1, str2) != 3) &&
            (sscanf(str, "%s for %s", str1, str2) != 2))
        {
            str2 = "";
            if (sscanf(str, "%d %s", number, str1) != 2)
                str1 = str;
        }
    }

    if (number <= 0)
        number = 1;

    if (number > 20)
        number = 20;

    if (FIREKNIVES_MAPPINGS->query_assassin_rank(this_player()->query_name())
        <= MAX_PROSPECT_RANK)
    {
        if (!this_player()->query_wiz_level())
        {
            notify_fail("As a Trainee, you currently have no permission to buy "
            +"herbs from the store.\n");
            return 0;
        }            
    }

    store = find_object(store_room);
    herbs = store->query_herbs();
    herb_files = filter(m_indexes(herbs), &filter_herb_name(,str1));

    if (sizeof(herb_files) > 0)
    {
    //    for (i = 0; i < sizeof(herb_files); i++)
    //    {
        max_num = 1;

        if (number > 1)
        {
            max_num = store->query_herb_number(herb_files[0]);
            if (number > max_num)
                number = max_num;
        }

        for (j = 0; j < number; j++)
            item += ({ clone_object(herb_files[0]) });
    }

    if (!sizeof(item))
        return shop_hook_buy_no_match(str1);

    if (query_shop_hook_restricted_herb(this_player(), str1))
        return shop_hook_restricted_herb(this_player(), str1);

    bought_item = buy_it(item, str2, str3);
    item -= bought_item;

    // remove herbs that were not bought
    if (sizeof(item))
        item->remove_object();

    if (sizeof(bought_item))
    {
        store->reduce_herb_number(bought_item);
        return shop_hook_bought_items(bought_item);
    }

    return 0; /* Player tried to buy a non buyable object. */
}

/*
 * Function name: shop_hook_value_held
 * Description:   Player values an object he's holding
 * Arguments:     ob   - The object
 *                text - The price in text form
 */
void
shop_hook_value_held(object ob, string text)
{
    string  desc = ob->query_id_long();

    write("You ask the shop keeper about the "
      + ob->query_short() + ".\n"
      + "You would get " + text + " for the "
      + ob->query_herb_name() + ".\n");
}

/*
 * Function name:   do_value
 * Description:     Let the player value an item, carry or in shop
 * Returns:         1 on success
 */
int
do_value(string str)
{
    object *item, store;
    int *arr, price, i, j, num;

    if (query_shop_no_business(this_player()))
    {
        shop_hook_no_business(this_player());
        return 0;
    }

    if (!str || str =="")
    {
        notify_fail("Value what?");
        return 0;
    }

    num = sizeof(query_money_types());
    item = FIND_STR_IN_OBJECT(str, this_player());

    if (!sizeof(item))
        return shop_hook_value_no_match(str);

    for (i = 0; i < sizeof(item); i++)
    {
        if (!shop_hook_allow_sell(item[i]) ||
          item[i]->query_prop(OBJ_M_NO_SELL)) 
        {
            shop_hook_value_not_interesting(item[i]);
            continue;
        }

        if (!(price = query_sell_price(item[i])))
        {
            shop_hook_value_not_interesting(item[i]);
            continue;
        }

        arr = calc_change(price, 0, "");
        shop_hook_value_held(item[i], text(arr));
        j++;
    }

    shop_hook_value_asking(str);

    if (j > 0)
        return 1;

    return 0;
}


int
do_sell(string args)
{
    if (query_shop_no_business(this_player()))
    {
        shop_hook_no_business(this_player());
        return 0;
    }

    return ::do_sell(args);
}


/*
 * Function name: sell_it
 * Description:   Try to let the player sell the item array
 * Arguments:     ob - the object array
 *                check - wheather check for worn or wielded stuff
 *                str - string describing how the money should be paid
 * Returns:   An array with the objects sold
 */
object *
sell_it(object *ob, string str, int check) 
{
    int     price, i, j, k, *tmp_arr, *null, *value_arr, *null_arr, err;
    object *sold;
    mixed   tmp;

    call_other(store_room, "load_me"); /* Make sure store room is loaded */

    value_arr = allocate(sizeof(query_money_types()));
    null_arr = value_arr + ({});
    sold = allocate(sizeof(ob));

    for (i = 0; i < sizeof(ob); i++)
    {
        if (!shop_hook_allow_sell(ob[i]))
            continue;

        if (ob[i]->query_herb_value() == 0)
        {
            shop_hook_sell_no_value(ob[i]);
            continue;
        }

        if (check && (ob[i]->query_worn() ||
            ob[i]->query_wielded()))
        {
            shop_hook_sell_worn_or_wielded(ob[i]);
            continue;
        }

        if (tmp = ob[i]->query_prop(OBJ_M_NO_SELL))
        {
            shop_hook_sell_no_sell(ob[i], tmp);
            continue;
        }

        /* Save price if ob destructed in move */
        price = query_sell_price(ob[i]);

        if (price <= 0)
        {
            shop_hook_sell_no_value(ob[i]);
            continue;
        }

        if (err = ob[i]->move(store_room))
        {
            shop_hook_sell_object_stuck(ob[i], err);
            continue;
        }

        if (price > 0)
        {
            tmp_arr = calc_change(price, null, str);

            for (k = 0; k < sizeof(value_arr); k++)
                value_arr[k] += tmp_arr[k];

            sold[j] = ob[i];
            j++;
            
            if (j >= 20)
                break;
            /*
             * Only let people sell 20 objects at once and hopefully we wont get
             * those too long evaluation problems.
             */
        }
    }

    sold = sold - ({ 0 });

    if (sizeof(sold) > 0)
    {
        change_money(null_arr + value_arr, this_player());
        shop_hook_sell_get_money(text(value_arr));
    }

    return sold;
}

void
smell_herbs()
{
    write("You cannot smell the herbs themselves since " +
    "they are hanging far out of your reach under the " +
    "ceiling, but their smell pervades the whole room.\n");
    return;
}

void
smell_air()
{
    write("The air is filled by the smell of the herbs " +
    "hanging under the ceiling. But they cannot completely " +
    "cover the sickly sweet smell of decay that drifts " +
    "through all the rooms here.\n");
    return;
}

int
do_smell(string str)
{
    NF("Smell what?\n");

    if (str == "herb" || str == "herbs")
    {
    smell_herbs();
    return 1;
    }
    if (str == "air")
    {
    smell_air();
    return 1;
    }
    return 0;
}

int
shop_hook_bought_items(object *arr)
{
    write(break_string("You bought " + COMPOSITE_DEAD(arr) + ".\n", 75));
    say(QCTNAME(this_player()) + " bought " + QCOMPDEAD + ".\n");
    arr->force_dry();
    return 1;
}

/*
 * Function name: buy_it
 * Description:   Try to let the player buy the item array
 *                The function in /lib/shop permits buying of only one item at a time.
 * Arguments:     ob - the object array
 *                str2 - string describing how the money should be paid
 *                str3 - what coin types to get chainge back in
 * Returns:       1 on sucess
 */
object *
buy_it(object *ob, string str2, string str3) 
{
    int price, i, j, k, *value_arr, *arr, error, num, err;
    object *bought;
    mixed tmp;

    num = sizeof(query_money_types());
    value_arr = allocate(2 * num);
    bought = allocate(sizeof(ob));

    for (i = 0; i < sizeof(ob); i++)
    {
        if (!shop_hook_allow_buy(ob[i]))
            continue;

        if (tmp = ob[i]->query_prop(OBJ_M_NO_BUY))
        {
            shop_hook_buy_no_buy(ob[i], tmp);
            continue;
        }

        price = query_buy_price(ob[i]);

        /* If you don't feel greedy you can shorten the calculation above. */

        if (err = ob[i]->move(this_player()))
        {
            shop_hook_buy_cant_carry(ob[i], err);
            break;
        }

        if (sizeof(arr = pay(price, this_player(), str2, 0, 0, str3)) == 1)
        {
            shop_hook_buy_cant_pay(ob[i], arr);
            break;  /* pay() can handle notify_fail() call */
        }

        /* Detect if there was a move error. */
        if (error = arr[sizeof(arr) - 1])
        {
            if (error < -1)
            {
                /* Couldn't take the money from player, the coins were stuck */
                shop_hook_buy_magic_money(ob[i]);
                continue;
            }
            /* We don't want the money so no move error to us, if there was one
               it was because the player couldn't hold all coins, and if so the
               drop text is already written, but the deal is still on :) */
        }

        for (k = 0; k < 2 * num; k++)
            value_arr[k] += arr[k];

        bought[j] = ob[i];
        j++;
    }

    bought = bought - ({ 0 });

    if (sizeof(bought) > 0)
        shop_hook_buy_pay_money(
          text(value_arr[0 .. num - 1]), text(value_arr[num .. 2 * num - 1]));

    return bought;
}
