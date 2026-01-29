/*
 * waterdeep/std/waterdeep_room.c
 * Waterdeep standard room
 *
 * 2021/01: Created by Brine
 */
#pragma strict_types

#include "../defs.h"
inherit FAERUN_OUTDOOR_BASE;

#include "waterdeep_room_flair.o"

void
create_waterdeep_room()
{
  // This function will likely be shadowed in higher level std rooms, and
  // the statements below will have to be included in those std rooms in
  // some form.
  set_short("This is the standard Waterdeep outdoor room");
  extraline = "\nLong outdoor room description.\n";

  add_prop(IS_WATERDEEP_ROOM, 1);
}

void
create_faerun_room()
{
  create_waterdeep_room();
}

void
set_area(string area_name)
{
  // This function should be overridden in higher level standard rooms
  string desc = "You are in the general area of your vicinity.\n";
  switch (area_name)
  {
    case CASTLE_WARD:
      desc = "You are in the Castle Ward of the City of Waterdeep.\n";
      break;
    case DEAD_WARD:
      desc = "You are in the City of the Dead within the City of Waterdeep.\n";
      break;
    case DOCK_WARD:
      desc = "You are in the Dock Ward of the City of Waterdeep.\n";
      break;
    case FIELD_WARD:
      desc = "You are in the Field Ward of the City of Waterdeep.\n";
      break;
    case MNT_WATERDEEP:
      desc = "You are on the slopes of Mount Waterdeep in the City of "
        + "Waterdeep.\n";
      break;
    case MOUNTAINSIDE:
      desc = "You are in the mountainside area in the City of Waterdeep.\n";
      break;
    case NORTH_WARD:
      desc = "You are in the North Ward of the City of Waterdeep.\n";
      break;
    case SEA_WARD:
      desc = "You are in the Sea Ward of the City of Waterdeep.\n";
      break;
    case SOUTHERN_WARD:
      desc = "You are in the Southern Ward of the City of Waterdeep.\n";
      break;
    case TRADES_WARD:
      desc = "You are in the Trades Ward of the City of Waterdeep.\n";
      break;
    case UNDERCLIFF:
      desc = "You are in the Undercliff area, outside the City of " +
      "Waterdeep.\n";
      break;
    case OUTSKIRTS:
      desc = "You are in the outskirts of the City of Waterdeep.\n";
      break;
    case TROLLWALL:
      desc = "You are on the Trollwall, the uttermost defenses of the City "
        + "of Waterdeep.\n";
      break;
  }

  add_prop(WATERDEEP_AREA, area_name);
  add_item(({ "area", "general area" }), desc);
}

void
set_road_type(string type)
{
  string *items = ({ "ground", "road" });
  string desc = "You are standing on solid, firm ground.\n";

  switch (type)
  {
    case DIRT_ROAD:
      items += ({ "dirt road" });
      desc = "You are standing on a dirt road, carving its way through the "
        + "area. Deep ruts tell the tale of a road well travelled.\n";
      add_item(({ "rut", "deep rut", "ruts", "deep ruts" }),
        "The ruts are deep and numerous, made by the wheels of numerous carts "
        + "and carriages passing through.\n");
      break;
    case HIGH_ROAD:
      items += ({
        "paved road", "high road", "highroad", "High Road", "the High Road",
        "the high road", "the highroad", "the Highroad", "Highroad"
      });
      desc = "You are standing on the High Road, the main traid route of "
      + "the northwestern Sword Coast. The road is wide and paved with "
      + "large cobbles. It seems old and well travelled.\n";
      add_item(
        ({
          "paving", "pavings", "stones", "paving stones", "cobbles", "tops"
        }),
        "They are rectangular shaped paving stones with curved tops. They are "
        + "laid into the road and look worn.\n"
      );
      break;
    case BOARDWALK_STREET:
      items += ({
        "plank", "boardwalk", "board walk", "planks", "boards", "walkway",
        "wooden plank", "wooden planks", "street", "boards of wooden planks"
      });
      desc = "You are standing on an elevated walkway made up of boards of "
        + " wooden planks.\n";
      break;
    case COBBLED_STREET:
      items += ({ "cobbles", "cobblestone", "cobblestones", "street", "way" });
      desc = "You are standing on a posh city street. Finely hewn "
        + "cobblestones pave the way, and a gutter runs alongside it.\n";
      add_item(
        ({ "gutter", "through", "stone through" }),
        "It is a shallow stone through to drain water away from the street.\n"
      );
      break;
    case DIRT_STREET:
      items += ({ "street", "dirt street", "dirt" });
      desc = "You are standing on a dirt street, carving its way through the "
        + "area. Deep ruts tell the tale of a street well travelled.\n";
      add_item(({ "rut", "deep rut", "ruts", "deep ruts" }),
        "The ruts are deep and numerous, made by the wheels of numerous carts "
        + "and carriages passing through.\n");
      break;
    case FILTHY_STREET:
      items += ({ "street", "dirt", "rancid dirt", "surroundings" });
      desc = "You are hard pressed to determine whether you are standing in a "
        + "street or a pigsty, your immediate surroundings comprise rancid "
        + "dirt of such origins as are best not to consider. Thankfully, "
        + "planks are interspersed to allow for (mostly) dry-shoed passage "
        + "through the area.\n";
      add_item(
        ({ "plank", "planks", "walkway" }),
        "Planks are laid out to form a makeshift walkway, providing an "
        + "opportunity to traverse the area without stepping in the rancid "
        + "dirt.\n"
      );
      break;
  }

  add_item(items, desc);
}
