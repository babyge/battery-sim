#include "widget.h"

#include "color.h"
#include "display.h"
//#include "desktop.h"

Widget *Widget::selectedWidget = nullptr;

Widget::Widget() {
	/* Initialize all members with default values */
	parent = nullptr;
	firstChild = nullptr;
	next = nullptr;

	position = {0, 0};
	size = {0, 0};

    visible = true;
    selected = false;
    selectable = true;
    redraw = true;
    redrawClear = false;
    redrawChild = false;
}

Widget::~Widget() {
	/* Remove the widget from its parents list */
	if(parent) {
		/* remove widget from parent linked list */
		Widget *it = parent->firstChild;
		/* which pointer is pointing to it */
		Widget **pointer = &(parent->firstChild);
		while (it) {
			if (it == this) {
				/* found this widget */
				/* set pointer to point to next widget, removing this widget from the list */
				*pointer = it->next;
				/* widget found, loop is done */
				break;
			} else {
				/* not this widget, update it and pointer to it */
				pointer = &(it->next);
				it = it->next;
			}
		}
		// TODO was this necessary?
//		/* request full redraw for parent */
//		widget_RequestRedrawFull(w->parent);
	}

	/* Delete all of its children */
	while (firstChild) {
		delete firstChild;
	}
}

void Widget::draw(Widget *w, coords_t pos) {
	/* calculate new position */
	pos.x += w->position.x;
	pos.y += w->position.y;
	if (w->redraw) {
		if (w->redrawClear) {
			if (w->selectable) {
				display_SetForeground(COLOR_BG_DEFAULT);
			} else {
				display_SetForeground(COLOR_UNSELECTABLE);
			}
			/* widget needs a full redraw, clear widget area */
			display_RectangleFull(pos.x, pos.y, pos.x + w->size.x - 1,
					pos.y + w->size.y - 1);
			/* clear flag */
			w->redrawClear = false;
		}
		/* draw widget */
		w->draw(pos);
		/* clear redraw request */
		w->redraw = false;
	}
	if (w->redrawChild) {
		/* draw children of this widget */
		w->drawChildren(pos);
		/* clear redraw request */
		w->redrawChild = false;
	}
}

void Widget::input(Widget *w, GUIEvent_t* ev) {
	switch (ev->type) {
	case EVENT_TOUCH_PRESSED:
	case EVENT_TOUCH_RELEASED:
		/* position based event */
		/* remove offset of own widget */
		ev->pos.x -= w->position.x;
		ev->pos.y -= w->position.y;
		/* first, try to handle it itself */
		w->input(ev);
		if (ev->type != EVENT_NONE) {
			/* event not handled yet */
			/* find matching child */
			Widget *child = w->firstChild;
			for (; child; child = child->next) {
				if (child->selectable) {
					/* potential candidate, check position */
					if (ev->pos.x >= child->position.x
							&& ev->pos.x <= child->position.x + child->size.x
							&& ev->pos.y >= child->position.y
							&& ev->pos.y <= child->position.y + child->size.y) {
						/* event is in child region */
						input(child, ev);
						/* send event only to first match */
						return;
					}
				}
			}
			/* Couldn't find any matching children -> this widget will be selected */
			if (ev->type == EVENT_TOUCH_PRESSED)
				w->select();
		} else {
			/* widget handled the input itself -> it is now selected */
			if (ev->type == EVENT_TOUCH_PRESSED)
				w->select();
		}
		break;
	case EVENT_BUTTON_CLICKED:
	case EVENT_ENCODER_MOVED:
		w->input(ev);
		break;
	default:
		break;
	}
}

void Widget::select() {
	if(this != selectedWidget) {
		/* de-select currently selected widget */
		if (selectedWidget) {
			selectedWidget->selected = false;
			selectedWidget->requestRedraw();
		}
		selectedWidget = this;
		selected = true;
		requestRedraw();
		// TODO
//		if ((w && !selectedWidget) || (!w && selectedWidget)) {
//			/* focus changed from/to desktop */
//			selectedWidget = w;
//			desktop_Draw();
//		} else {
//			selectedWidget = w;
//		}
	}
}

void Widget::requestRedrawChildren() {
	if (!firstChild) {
		/* Widget does not have any children */
		return;
	}
	/* iterate over all widgets and request a redraw them */
	redrawChild = true;
	Widget *w = firstChild;
	while (w) {
		w->redraw = true;
		/* recursively request redraw of their children */
		if (w->firstChild) {
			/* widget got children itself */
			w->requestRedrawChildren();
		}
		w = w->next;
	}
}

void Widget::requestRedraw() {
	/* mark this widget */
	redraw = true;
	Widget *w = parent;
	while(w) {
		/* this is not the top widget, indicate branch redraw */
		if (w->redrawChild) {
			/* reached a part that is already scheduled for redrawing */
			break;
		}
		w->redrawChild = true;
		w = w->parent;
	}
}

void Widget::requestRedrawFull() {
	/* mark this widget */
	redrawClear = true;
	/* mark all children */
	if (firstChild) {
		requestRedrawChildren();
	}
	/* mark parents */
	requestRedraw();
}

bool Widget::isInArea(coords_t pos) {
	if (pos.x >= position.x && pos.x < position.x + size.x
			&& pos.y >= position.y && pos.y < position.y + size.y) {
		return true;
	} else {
		return false;
	}
}
