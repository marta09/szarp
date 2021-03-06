/* 
 * SZARP: SCADA software 
 *
 * Copyright (C) 
 * 2011 - Jakub Kotur <qba@newterm.pl>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 * 
 */
/** 
 * @file log_params.h
 * @brief File with list of activity params that may be logged.
 *
 * This file contains static table witch defines activity parameters.
 * This is necessary for building TSzarpConfig based on this configuration,
 * cause parcook doesn't provide any way for dynamic parameters adding.
 * If parameter is not listed below it will be not logged by logdmn.
 *
 * @author Jakub Kotur <qba@newterm.pl>
 * @version 0.2
 * @date 2011-10-10
 */


#ifndef __LOG_PARAMS_H__

#define __LOG_PARAMS_H__

#include "log_prefix.h"

#define LOG_PARAMS_NUMBER 250
const wchar_t* LOG_PARAMS[LOG_PARAMS_NUMBER][3] = {
	{ LOG_PREFIX L":draw3:codeedit:size" , L"log" , L"codeedit:size" }, 
	{ LOG_PREFIX L":draw3:codeedit:clear" , L"log" , L"codeedit:clear" }, 
	{ LOG_PREFIX L":draw3:codeedit:cut" , L"log" , L"codeedit:cut" }, 
	{ LOG_PREFIX L":draw3:codeedit:copy" , L"log" , L"codeedit:copy" }, 
	{ LOG_PREFIX L":draw3:codeedit:paste" , L"log" , L"codeedit:paste" }, 
	{ LOG_PREFIX L":draw3:codeedit:indentinc" , L"log" , L"codeedit:indentinc" }, 
	{ LOG_PREFIX L":draw3:codeedit:indentred" , L"log" , L"codeedit:indentred" }, 
	{ LOG_PREFIX L":draw3:codeedit:selectall" , L"log" , L"codeedit:selectall" }, 
	{ LOG_PREFIX L":draw3:codeedit:selectline" , L"log" , L"codeedit:selectline" }, 
	{ LOG_PREFIX L":draw3:codeedit:redo" , L"log" , L"codeedit:redo" }, 
	{ LOG_PREFIX L":draw3:codeedit:undo" , L"log" , L"codeedit:undo" }, 
	{ LOG_PREFIX L":draw3:codeedit:bracematch" , L"log" , L"codeedit:bracematch" }, 
	{ LOG_PREFIX L":draw3:codeedit:indentguide" , L"log" , L"codeedit:indentguide" }, 
	{ LOG_PREFIX L":draw3:codeedit:linenumber" , L"log" , L"codeedit:linenumber" }, 
	{ LOG_PREFIX L":draw3:codeedit:longlineon" , L"log" , L"codeedit:longlineon" }, 
	{ LOG_PREFIX L":draw3:codeedit:whitespace" , L"log" , L"codeedit:whitespace" }, 
	{ LOG_PREFIX L":draw3:codeedit:foldtoggle" , L"log" , L"codeedit:foldtoggle" }, 
	{ LOG_PREFIX L":draw3:codeedit:overtype" , L"log" , L"codeedit:overtype" }, 
	{ LOG_PREFIX L":draw3:codeedit:readonly" , L"log" , L"codeedit:readonly" }, 
	{ LOG_PREFIX L":draw3:codeedit:wrapmodeon" , L"log" , L"codeedit:wrapmodeon" }, 
	{ LOG_PREFIX L":draw3:codeedit:" , L"log" , L"codeedit:" }, 
	{ LOG_PREFIX L":draw3:remarks:ok" , L"log" , L"remarks:ok" }, 
	{ LOG_PREFIX L":draw3:remarks:pass" , L"log" , L"remarks:pass" }, 
	{ LOG_PREFIX L":draw3:drawapp:start" , L"log" , L"drawapp:start" }, 
	{ LOG_PREFIX L":draw3:drawfrm:quit" , L"log" , L"drawfrm:quit" }, 
	{ LOG_PREFIX L":draw3:drawfrm:about" , L"log" , L"drawfrm:about" }, 
	{ LOG_PREFIX L":draw3:drawfrm:help" , L"log" , L"drawfrm:help" }, 
	{ LOG_PREFIX L":draw3:drawfrm:find" , L"log" , L"drawfrm:find" }, 
	{ LOG_PREFIX L":draw3:drawfrm:setparams" , L"log" , L"drawfrm:setparams" }, 
	{ LOG_PREFIX L":draw3:drawfrm:clearcache" , L"log" , L"drawfrm:clearcache" }, 
	{ LOG_PREFIX L":draw3:drawfrm:editset" , L"log" , L"drawfrm:editset" }, 
	{ LOG_PREFIX L":draw3:drawfrm:editasnew" , L"log" , L"drawfrm:editasnew" }, 
	{ LOG_PREFIX L":draw3:drawfrm:importset" , L"log" , L"drawfrm:importset" }, 
	{ LOG_PREFIX L":draw3:drawfrm:exportset" , L"log" , L"drawfrm:exportset" }, 
	{ LOG_PREFIX L":draw3:drawfrm:delset" , L"log" , L"drawfrm:delset" }, 
	{ LOG_PREFIX L":draw3:drawfrm:newset" , L"log" , L"drawfrm:newset" }, 
	{ LOG_PREFIX L":draw3:drawfrm:save" , L"log" , L"drawfrm:save" }, 
	{ LOG_PREFIX L":draw3:drawfrm:newwindow" , L"log" , L"drawfrm:newwindow" }, 
	{ LOG_PREFIX L":draw3:drawfrm:newtab" , L"log" , L"drawfrm:newtab" }, 
	{ LOG_PREFIX L":draw3:drawfrm:closetab" , L"log" , L"drawfrm:closetab" }, 
	{ LOG_PREFIX L":draw3:drawfrm:summary" , L"log" , L"drawfrm:summary" }, 
	{ LOG_PREFIX L":draw3:drawfrm:jump" , L"log" , L"drawfrm:jump" }, 
	{ LOG_PREFIX L":draw3:drawfrm:axes" , L"log" , L"drawfrm:axes" }, 
	{ LOG_PREFIX L":draw3:drawfrm:print" , L"log" , L"drawfrm:print" }, 
	{ LOG_PREFIX L":draw3:drawfrm:printprev" , L"log" , L"drawfrm:printprev" }, 
	{ LOG_PREFIX L":draw3:drawfrm:f0" , L"log" , L"drawfrm:f0" }, 
	{ LOG_PREFIX L":draw3:drawfrm:f1" , L"log" , L"drawfrm:f1" }, 
	{ LOG_PREFIX L":draw3:drawfrm:f2" , L"log" , L"drawfrm:f2" }, 
	{ LOG_PREFIX L":draw3:drawfrm:f3" , L"log" , L"drawfrm:f3" }, 
	{ LOG_PREFIX L":draw3:drawfrm:f4" , L"log" , L"drawfrm:f4" }, 
	{ LOG_PREFIX L":draw3:drawfrm:f5" , L"log" , L"drawfrm:f5" }, 
	{ LOG_PREFIX L":draw3:drawfrm:pie" , L"log" , L"drawfrm:pie" }, 
	{ LOG_PREFIX L":draw3:drawfrm:ratio" , L"log" , L"drawfrm:ratio" }, 
	{ LOG_PREFIX L":draw3:drawfrm:xygraph" , L"log" , L"drawfrm:xygraph" }, 
	{ LOG_PREFIX L":draw3:drawfrm:xyzgraph" , L"log" , L"drawfrm:xyzgraph" }, 
	{ LOG_PREFIX L":draw3:drawfrm:showremarks" , L"log" , L"drawfrm:showremarks" }, 
	{ LOG_PREFIX L":draw3:drawfrm:statswin" , L"log" , L"drawfrm:statswin" }, 
	{ LOG_PREFIX L":draw3:drawfrm:fullscreen" , L"log" , L"drawfrm:fullscreen" }, 
	{ LOG_PREFIX L":draw3:drawfrm:splitcursor" , L"log" , L"drawfrm:splitcursor" }, 
	{ LOG_PREFIX L":draw3:drawfrm:latestdata" , L"log" , L"drawfrm:latestdata" }, 
	{ LOG_PREFIX L":draw3:drawfrm:decade" , L"log" , L"drawfrm:decade" }, 
	{ LOG_PREFIX L":draw3:drawfrm:year" , L"log" , L"drawfrm:year" }, 
	{ LOG_PREFIX L":draw3:drawfrm:month" , L"log" , L"drawfrm:month" }, 
	{ LOG_PREFIX L":draw3:drawfrm:week" , L"log" , L"drawfrm:week" }, 
	{ LOG_PREFIX L":draw3:drawfrm:day" , L"log" , L"drawfrm:day" }, 
	{ LOG_PREFIX L":draw3:drawfrm:30min" , L"log" , L"drawfrm:30min" }, 
	{ LOG_PREFIX L":draw3:drawfrm:season" , L"log" , L"drawfrm:season" }, 
	{ LOG_PREFIX L":draw3:drawfrm:copy" , L"log" , L"drawfrm:copy" }, 
	{ LOG_PREFIX L":draw3:drawfrm:paste" , L"log" , L"drawfrm:paste" }, 
	{ LOG_PREFIX L":draw3:drawfrm:cpyparam" , L"log" , L"drawfrm:cpyparam" }, 
	{ LOG_PREFIX L":draw3:drawfrm:importdraw2" , L"log" , L"drawfrm:importdraw2" }, 
	{ LOG_PREFIX L":draw3:drawfrm:reload" , L"log" , L"drawfrm:reload" }, 
	{ LOG_PREFIX L":draw3:drawfrm:showerror" , L"log" , L"drawfrm:showerror" }, 
	{ LOG_PREFIX L":draw3:drawfrm:userparams" , L"log" , L"drawfrm:userparams" }, 
	{ LOG_PREFIX L":draw3:drawfrm:language" , L"log" , L"drawfrm:language" }, 
	{ LOG_PREFIX L":draw3:drawfrm:graphs" , L"log" , L"drawfrm:graphs" }, 
	{ LOG_PREFIX L":draw3:drawfrm:refresh" , L"log" , L"drawfrm:refresh" }, 
	{ LOG_PREFIX L":draw3:drawfrm:contexthelp" , L"log" , L"drawfrm:contexthelp" }, 
	{ LOG_PREFIX L":draw3:drawfrm:numberofpoints" , L"log" , L"drawfrm:numberofpoints" }, 
	{ LOG_PREFIX L":draw3:drawfrm:add_remark" , L"log" , L"drawfrm:add_remark" }, 
	{ LOG_PREFIX L":draw3:drawfrm:fetch_remarks" , L"log" , L"drawfrm:fetch_remarks" }, 
	{ LOG_PREFIX L":draw3:drawfrm:remarks_config" , L"log" , L"drawfrm:remarks_config" }, 
	{ LOG_PREFIX L":draw3:drawfrm:page_setup" , L"log" , L"drawfrm:page_setup" }, 
	{ LOG_PREFIX L":draw3:drawfrm:prober_adress" , L"log" , L"drawfrm:prober_adress" },
	{ LOG_PREFIX L":draw3:drawfrm:sortavg" , L"log" , L"drawfrm:sortavg" }, 
	{ LOG_PREFIX L":draw3:drawfrm:sortmax" , L"log" , L"drawfrm:sortmax" }, 
	{ LOG_PREFIX L":draw3:drawfrm:sortmin" , L"log" , L"drawfrm:sortmin" }, 
	{ LOG_PREFIX L":draw3:drawfrm:sorthour" , L"log" , L"drawfrm:sorthour" }, 
	{ LOG_PREFIX L":draw3:drawfrm:sortnone" , L"log" , L"drawfrm:sortnone" }, 
	{ LOG_PREFIX L":draw3:drawfrm:tb_exit" , L"log" , L"drawfrm:tb_exit" }, 
	{ LOG_PREFIX L":draw3:drawfrm:tb_about" , L"log" , L"drawfrm:tb_about" }, 
	{ LOG_PREFIX L":draw3:drawfrm:tb_remark" , L"log" , L"drawfrm:tb_remark" }, 
	{ LOG_PREFIX L":draw3:drawfrm:tb_gotolatest" , L"log" , L"drawfrm:tb_gotolatest" }, 
	{ LOG_PREFIX L":draw3:drawfrm:gotolatest" , L"log" , L"drawfrm:gotolatest" }, 
	{ LOG_PREFIX L":draw3:drawfrm:search_date" , L"log" , L"drawfrm:search_date" }, 
	{ LOG_PREFIX L":draw3:drawfrm:close" , L"log" , L"drawfrm:close" }, 
	{ LOG_PREFIX L":draw3:drawpick:edit_ok" , L"log" , L"drawpick:edit_ok" }, 
	{ LOG_PREFIX L":draw3:drawpick:edit_cancel" , L"log" , L"drawpick:edit_cancel" }, 
	{ LOG_PREFIX L":draw3:drawpick:edit_colour" , L"log" , L"drawpick:edit_colour" }, 
	{ LOG_PREFIX L":draw3:drawpick:edit_scale" , L"log" , L"drawpick:edit_scale" }, 
	{ LOG_PREFIX L":draw3:drawpick:picker_ok" , L"log" , L"drawpick:picker_ok" }, 
	{ LOG_PREFIX L":draw3:drawpick:picker_cancel" , L"log" , L"drawpick:picker_cancel" }, 
	{ LOG_PREFIX L":draw3:drawpick:picker_help" , L"log" , L"drawpick:picker_help" }, 
	{ LOG_PREFIX L":draw3:drawpick:picker_add_draw" , L"log" , L"drawpick:picker_add_draw" }, 
	{ LOG_PREFIX L":draw3:drawpick:picker_add_param" , L"log" , L"drawpick:picker_add_param" }, 
	{ LOG_PREFIX L":draw3:drawpick:picker_tb_remove" , L"log" , L"drawpick:picker_tb_remove" }, 
	{ LOG_PREFIX L":draw3:drawpick:picker_tb_edit" , L"log" , L"drawpick:picker_tb_edit" }, 
	{ LOG_PREFIX L":draw3:drawpick:picker_tb_up" , L"log" , L"drawpick:picker_tb_up" }, 
	{ LOG_PREFIX L":draw3:drawpick:picker_tb_down" , L"log" , L"drawpick:picker_tb_down" }, 
	{ LOG_PREFIX L":draw3:drawpick:picker_tb_param_edit" , L"log" , L"drawpick:picker_tb_param_edit" }, 
	{ LOG_PREFIX L":draw3:drawpick:picker_bitmap_up" , L"log" , L"drawpick:picker_bitmap_up" }, 
	{ LOG_PREFIX L":draw3:drawpick:picker_bitmap_down" , L"log" , L"drawpick:picker_bitmap_down" }, 
	{ LOG_PREFIX L":draw3:drawpick:picker_close" , L"log" , L"drawpick:picker_close" }, 
	{ LOG_PREFIX L":draw3:drawpick:picker_char" , L"log" , L"drawpick:picker_char" }, 
	{ LOG_PREFIX L":draw3:drawpnl:key_char" , L"log" , L"drawpnl:key_char" }, 
	{ LOG_PREFIX L":draw3:drawpnl:on_key_down" , L"log" , L"drawpnl:on_key_down" }, 
	{ LOG_PREFIX L":draw3:drawpnl:on_key_up" , L"log" , L"drawpnl:on_key_up" }, 
	{ LOG_PREFIX L":draw3:drawpnl:refresh" , L"log" , L"drawpnl:refresh" }, 
	{ LOG_PREFIX L":draw3:drawpnl:find" , L"log" , L"drawpnl:find" }, 
	{ LOG_PREFIX L":draw3:drawpnl:summary" , L"log" , L"drawpnl:summary" }, 
	{ LOG_PREFIX L":draw3:drawpnl:f0" , L"log" , L"drawpnl:f0" }, 
	{ LOG_PREFIX L":draw3:drawpnl:f1" , L"log" , L"drawpnl:f1" }, 
	{ LOG_PREFIX L":draw3:drawpnl:f2" , L"log" , L"drawpnl:f2" }, 
	{ LOG_PREFIX L":draw3:drawpnl:f3" , L"log" , L"drawpnl:f3" }, 
	{ LOG_PREFIX L":draw3:drawpnl:f4" , L"log" , L"drawpnl:f4" }, 
	{ LOG_PREFIX L":draw3:drawpnl:f5" , L"log" , L"drawpnl:f5" }, 
	{ LOG_PREFIX L":draw3:drawpnl:tb_spltcrs" , L"log" , L"drawpnl:tb_spltcrs" }, 
	{ LOG_PREFIX L":draw3:drawpnl:tb_filter" , L"log" , L"drawpnl:tb_filter" }, 
	{ LOG_PREFIX L":draw3:drawpnl:drawtree" , L"log" , L"drawpnl:drawtree" }, 
	{ LOG_PREFIX L":draw3:drawpsc:choice" , L"log" , L"drawpsc:choice" }, 
	{ LOG_PREFIX L":draw3:drawpsc:close" , L"log" , L"drawpsc:close" }, 
	{ LOG_PREFIX L":draw3:drawtb:newdrawversion" , L"log" , L"drawtb:newdrawversion" }, 
	{ LOG_PREFIX L":draw3:drawtree:ok" , L"log" , L"drawtree:ok" }, 
	{ LOG_PREFIX L":draw3:drawtree:cancel" , L"log" , L"drawtree:cancel" }, 
	{ LOG_PREFIX L":draw3:drawtree:help" , L"log" , L"drawtree:help" }, 
	{ LOG_PREFIX L":draw3:errfrm:close" , L"log" , L"errfrm:close" }, 
	{ LOG_PREFIX L":draw3:errfrm:hide" , L"log" , L"errfrm:hide" }, 
	{ LOG_PREFIX L":draw3:errfrm:clear" , L"log" , L"errfrm:clear" }, 
	{ LOG_PREFIX L":draw3:errfrm:help" , L"log" , L"errfrm:help" }, 
	{ LOG_PREFIX L":draw3:frmmgr:close" , L"log" , L"frmmgr:close" }, 
	{ LOG_PREFIX L":draw3:gcdcg:mouse_left_down" , L"log" , L"gcdcg:mouse_left_down" }, 
	{ LOG_PREFIX L":draw3:gcdcg:mouse_left_click" , L"log" , L"gcdcg:mouse_left_click" }, 
	{ LOG_PREFIX L":draw3:gcdcg:mouse_left_up" , L"log" , L"gcdcg:mouse_left_up" }, 
	{ LOG_PREFIX L":draw3:gcdcg:size" , L"log" , L"gcdcg:size" }, 
	{ LOG_PREFIX L":draw3:incsearch:ok" , L"log" , L"incsearch:ok" }, 
	{ LOG_PREFIX L":draw3:incsearch:reset" , L"log" , L"incsearch:reset" }, 
	{ LOG_PREFIX L":draw3:incsearch:cancel" , L"log" , L"incsearch:cancel" }, 
	{ LOG_PREFIX L":draw3:incsearch:help" , L"log" , L"incsearch:help" }, 
	{ LOG_PREFIX L":draw3:incsearch:close" , L"log" , L"incsearch:close" }, 
	{ LOG_PREFIX L":draw3:incsearch:choise" , L"log" , L"incsearch:choise" }, 
	{ LOG_PREFIX L":draw3:incsearch:edit" , L"log" , L"incsearch:edit" }, 
	{ LOG_PREFIX L":draw3:incsearch:remove" , L"log" , L"incsearch:remove" }, 
	{ LOG_PREFIX L":draw3:incsearch:char" , L"log" , L"incsearch:char" }, 
	{ LOG_PREFIX L":draw3:paramlist:char" , L"log" , L"paramlist:char" }, 
	{ LOG_PREFIX L":draw3:paramlist:add" , L"log" , L"paramlist:add" }, 
	{ LOG_PREFIX L":draw3:paramlist:remove" , L"log" , L"paramlist:remove" }, 
	{ LOG_PREFIX L":draw3:paramlist:edit" , L"log" , L"paramlist:edit" }, 
	{ LOG_PREFIX L":draw3:paramlist:new" , L"log" , L"paramlist:new" }, 
	{ LOG_PREFIX L":draw3:paramlist:delete" , L"log" , L"paramlist:delete" }, 
	{ LOG_PREFIX L":draw3:paramlist:edit_but" , L"log" , L"paramlist:edit_but" }, 
	{ LOG_PREFIX L":draw3:paramlist:ok_but" , L"log" , L"paramlist:ok_but" }, 
	{ LOG_PREFIX L":draw3:paramlist:ok" , L"log" , L"paramlist:ok" }, 
	{ LOG_PREFIX L":draw3:paramlist:help" , L"log" , L"paramlist:help" }, 
	{ LOG_PREFIX L":draw3:paramlist:cancel" , L"log" , L"paramlist:cancel" }, 
	{ LOG_PREFIX L":draw3:paramlist:close_but" , L"log" , L"paramlist:close_but" }, 
	{ LOG_PREFIX L":draw3:paramlist:close" , L"log" , L"paramlist:close" }, 
	{ LOG_PREFIX L":draw3:paredit:cancel" , L"log" , L"paredit:cancel" }, 
	{ LOG_PREFIX L":draw3:paredit:ok" , L"log" , L"paredit:ok" }, 
	{ LOG_PREFIX L":draw3:paredit:help" , L"log" , L"paredit:help" }, 
	{ LOG_PREFIX L":draw3:paredit:help_search" , L"log" , L"paredit:help_search" }, 
	{ LOG_PREFIX L":draw3:paredit:forward" , L"log" , L"paredit:forward" }, 
	{ LOG_PREFIX L":draw3:paredit:backward" , L"log" , L"paredit:backward" }, 
	{ LOG_PREFIX L":draw3:paredit:close" , L"log" , L"paredit:close" }, 
	{ LOG_PREFIX L":draw3:paredit:form_undo" , L"log" , L"paredit:form_undo" }, 
	{ LOG_PREFIX L":draw3:paredit:form_redo" , L"log" , L"paredit:form_redo" }, 
	{ LOG_PREFIX L":draw3:paredit:form_add" , L"log" , L"paredit:form_add" }, 
	{ LOG_PREFIX L":draw3:paredit:form_sub" , L"log" , L"paredit:form_sub" }, 
	{ LOG_PREFIX L":draw3:paredit:form_multi" , L"log" , L"paredit:form_multi" }, 
	{ LOG_PREFIX L":draw3:paredit:form_div" , L"log" , L"paredit:form_div" }, 
	{ LOG_PREFIX L":draw3:paredit:form_insert_param" , L"log" , L"paredit:form_insert_param" }, 
	{ LOG_PREFIX L":draw3:paredit:form_ins_user_param" , L"log" , L"paredit:form_ins_user_param" }, 
	{ LOG_PREFIX L":draw3:paredit:base_config" , L"log" , L"paredit:base_config" }, 
	{ LOG_PREFIX L":draw3:paredit:degree" , L"log" , L"paredit:degree" }, 
	{ LOG_PREFIX L":draw3:paredit:checkbox_startdate" , L"log" , L"paredit:checkbox_startdate" }, 
	{ LOG_PREFIX L":draw3:probad:ok" , L"log" , L"probad:ok" }, 
	{ LOG_PREFIX L":draw3:probad:help" , L"log" , L"probad:help" }, 
	{ LOG_PREFIX L":draw3:probad:cancel" , L"log" , L"probad:cancel" }, 
	{ LOG_PREFIX L":draw3:probad:close" , L"log" , L"probad:close" }, 
	{ LOG_PREFIX L":draw3:remarksview:close" , L"log" , L"remarksview:close" }, 
	{ LOG_PREFIX L":draw3:remarksview:cancel" , L"log" , L"remarksview:cancel" }, 
	{ LOG_PREFIX L":draw3:remarksview:help" , L"log" , L"remarksview:help" }, 
	{ LOG_PREFIX L":draw3:remarksview:goto" , L"log" , L"remarksview:goto" }, 
	{ LOG_PREFIX L":draw3:remarksview:add" , L"log" , L"remarksview:add" }, 
	{ LOG_PREFIX L":draw3:remarks:open" , L"log" , L"remarks:open" }, 
	{ LOG_PREFIX L":draw3:remarks:close" , L"log" , L"remarks:close" }, 
	{ LOG_PREFIX L":draw3:remarks:help" , L"log" , L"remarks:help" }, 
	{ LOG_PREFIX L":draw3:seldraw:block" , L"log" , L"seldraw:block" }, 
	{ LOG_PREFIX L":draw3:seldraw:psc" , L"log" , L"seldraw:psc" }, 
	{ LOG_PREFIX L":draw3:seldraw:doc" , L"log" , L"seldraw:doc" }, 
	{ LOG_PREFIX L":draw3:seldraw:cpyparam" , L"log" , L"seldraw:cpyparam" }, 
	{ LOG_PREFIX L":draw3:seldraw:edit" , L"log" , L"seldraw:edit" }, 
	{ LOG_PREFIX L":draw3:statdiag:start_time" , L"log" , L"statdiag:start_time" }, 
	{ LOG_PREFIX L":draw3:statdiag:end_time" , L"log" , L"statdiag:end_time" }, 
	{ LOG_PREFIX L":draw3:statdiag:draw_button" , L"log" , L"statdiag:draw_button" }, 
	{ LOG_PREFIX L":draw3:statdiag:ok" , L"log" , L"statdiag:ok" }, 
	{ LOG_PREFIX L":draw3:statdiag:close" , L"log" , L"statdiag:close" }, 
	{ LOG_PREFIX L":draw3:statdiag:help" , L"log" , L"statdiag:help" }, 
	{ LOG_PREFIX L":draw3:statdiag:show" , L"log" , L"statdiag:show" }, 
	{ LOG_PREFIX L":draw3:statdiag:choice" , L"log" , L"statdiag:choice" }, 
	{ LOG_PREFIX L":draw3:timewdg:DECADE" , L"log" , L"timewdg:DECADE" }, 
	{ LOG_PREFIX L":draw3:timewdg:YEAR" , L"log" , L"timewdg:YEAR" }, 
	{ LOG_PREFIX L":draw3:timewdg:MONTH" , L"log" , L"timewdg:MONTH" }, 
	{ LOG_PREFIX L":draw3:timewdg:WEEK" , L"log" , L"timewdg:WEEK" }, 
	{ LOG_PREFIX L":draw3:timewdg:DAY" , L"log" , L"timewdg:DAY" }, 
	{ LOG_PREFIX L":draw3:timewdg:30 MINUTES" , L"log" , L"timewdg:30 MINUTES" }, 
	{ LOG_PREFIX L":draw3:timewdg:HOUR" , L"log" , L"timewdg:HOUR" }, 
	{ LOG_PREFIX L":draw3:timewdg:SEASON" , L"log" , L"timewdg:SEASON" }, 
	{ LOG_PREFIX L":draw3:xydiag:start_date" , L"log" , L"xydiag:start_date" }, 
	{ LOG_PREFIX L":draw3:xydiag:ok" , L"log" , L"xydiag:ok" }, 
	{ LOG_PREFIX L":draw3:xydiag:cancel" , L"log" , L"xydiag:cancel" }, 
	{ LOG_PREFIX L":draw3:xydiag:help" , L"log" , L"xydiag:help" }, 
	{ LOG_PREFIX L":draw3:xydiag:end_date" , L"log" , L"xydiag:end_date" }, 
	{ LOG_PREFIX L":draw3:xydiag:period_change" , L"log" , L"xydiag:period_change" }, 
	{ LOG_PREFIX L":draw3:xydiag:xaxis" , L"log" , L"xydiag:xaxis" }, 
	{ LOG_PREFIX L":draw3:xydiag:yaxis" , L"log" , L"xydiag:yaxis" }, 
	{ LOG_PREFIX L":draw3:xydiag:zaxis" , L"log" , L"xydiag:zaxis" }, 
	{ LOG_PREFIX L":draw3:xygraph:change_graph" , L"log" , L"xygraph:change_graph" }, 
	{ LOG_PREFIX L":draw3:xygraph:close_menu" , L"log" , L"xygraph:close_menu" }, 
	{ LOG_PREFIX L":draw3:xygraph:print_preview" , L"log" , L"xygraph:print_preview" }, 
	{ LOG_PREFIX L":draw3:xygraph:print_page_setup" , L"log" , L"xygraph:print_page_setup" }, 
	{ LOG_PREFIX L":draw3:xygraph:print" , L"log" , L"xygraph:print" }, 
	{ LOG_PREFIX L":draw3:xygraph:zoom_out" , L"log" , L"xygraph:zoom_out" }, 
	{ LOG_PREFIX L":draw3:xygraph:help" , L"log" , L"xygraph:help" }, 
	{ LOG_PREFIX L":draw3:xygraph:close" , L"log" , L"xygraph:close" }, 
	{ LOG_PREFIX L":draw3:xygraph:key_down" , L"log" , L"xygraph:key_down" }, 
	{ LOG_PREFIX L":draw3:xygraph:key_up" , L"log" , L"xygraph:key_up" }, 
	{ LOG_PREFIX L":draw3:xygraph:goto_graph" , L"log" , L"xygraph:goto_graph" }, 
	{ LOG_PREFIX L":draw3:xyzgraph:size" , L"log" , L"xyzgraph:size" }, 
	{ LOG_PREFIX L":draw3:xyzgraph:keyup" , L"log" , L"xyzgraph:keyup" }, 
	{ LOG_PREFIX L":draw3:xyzgraph:char" , L"log" , L"xyzgraph:char" }, 
	{ LOG_PREFIX L":draw3:xyzgraph:left_down" , L"log" , L"xyzgraph:left_down" }, 
	{ LOG_PREFIX L":draw3:xyzgraph:right_down" , L"log" , L"xyzgraph:right_down" }, 
	{ LOG_PREFIX L":draw3:xyzgraph:right_up" , L"log" , L"xyzgraph:right_up" }, 
	{ LOG_PREFIX L":draw3:xyzgraph:wheel" , L"log" , L"xyzgraph:wheel" }, 
	{ LOG_PREFIX L":draw3:xyzgraph:change_graph" , L"log" , L"xyzgraph:change_graph" }, 
	{ LOG_PREFIX L":draw3:xyzgraph:print" , L"log" , L"xyzgraph:print" }, 
	{ LOG_PREFIX L":draw3:xyzgraph:print_preview" , L"log" , L"xyzgraph:print_preview" }, 
	{ LOG_PREFIX L":draw3:xyzgraph:print_page_setup" , L"log" , L"xyzgraph:print_page_setup" }, 
	{ LOG_PREFIX L":draw3:xyzgraph:exit" , L"log" , L"xyzgraph:exit" }, 
	{ LOG_PREFIX L":draw3:xyzgraph:help" , L"log" , L"xyzgraph:help" }, 
};

#endif /* __LOG_PARAMS_H__ */

