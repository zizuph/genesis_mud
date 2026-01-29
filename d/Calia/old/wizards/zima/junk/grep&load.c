/* With this object you can do longer greps with one directory.
 * You need to cd into the correct dir and the use the format
 * 'grep <string>'. Grepping voluminous directories may take
 * some time.
 *
 * Grepper: Original code taken from Mrpr, modified to used alarms
 *          by Aridor
 *
 *
 * Also available in this object is a multiple file loader, with
 * which you can load all files in a directory. Use the syntax
 * 'loadmany <path&files>' where <path&files> can be a complete
 * of relative pathname, and also file selection with the * construct
 * is available, eg.  road*.    just giving * will load all files in
 * the currently active directory.
 *
 * Multiple File Loader: Original code taken from Plugh, Aridor fixed
 *                       a bug that prevented the use of relative
 *                       pathnames.
 *
 *
 * Aridor, 10/94
 */

inherit "/d/Krynn/aridor/grep&load";

/* This construct has been stolen from Napture, isn't that a nice one? :)
 */
