#ifndef GUI_WIDGET_H_
#define GUI_WIDGET_H_

#include <string.h>
#include <stdint.h>

#include "common.h"
#include "events.h"

class Widget {
	/* Classes which can have children need extended access to their childrens members */
	friend class Container;
	friend class Window;
public:
	Widget();
	virtual ~Widget();

	static void draw(Widget *w, coords_t pos);
	static void input(Widget *w, GUIEvent_t *ev);

	static Widget *getSelected() {
		return selectedWidget;
	}

	static void deselect() {
		if (selectedWidget) {
			selectedWidget->selected = false;
			selectedWidget->requestRedraw();
		}
	}

	void select();

	void requestRedrawChildren();
	void requestRedraw();
	void requestRedrawFull();

	void setSelectable(bool s) {
		if(s && !selectable) {
			selectable = true;
			requestRedrawFull();
		} else if(!s && selectable) {
			selectable = false;
			requestRedrawFull();
		}
	}

	void widget_SetVisible(bool v) {
		if(visible != v) {
			visible = v;
			requestRedrawFull();
		}
	}

	bool isInArea(coords_t pos);

	coords_t getSize() {
		return size;
	}

	void setPosition(coords_t pos) {
		position = pos;
	}

protected:
	virtual void draw(coords_t offset) { return; }
	virtual void input(GUIEvent_t *ev) { return; }
	virtual void drawChildren(coords_t offset) { return; }

	static Widget *selectedWidget;

	Widget *parent;
	Widget *firstChild;
	Widget *next;

	coords_t position;
	coords_t size;
	bool visible :1;
	bool selected :1;
	bool selectable :1;
//	bool focus :1;
	/* this widget needs to be redrawn */
	bool redraw :1;
	/* the widget area has to be cleared and the widget redrawn completely */
	bool redrawClear :1;
	/* some widget down this widgets branch has to be redrawn */
	bool redrawChild :1;
};

#endif
