#include "MenuItemToggleButton.h"

namespace AssortedWidgets
{
	namespace Widgets
	{
        MenuItemToggleButton::MenuItemToggleButton(std::string &_text)
            :m_text(_text),
              m_style(stretch),
              m_left(24),
              m_top(4),
              m_bottom(2),
              m_right(2),
              m_status(normal),
              m_toggle(false)
		{
            m_size=getPreferedSize();
		}

        MenuItemToggleButton::MenuItemToggleButton(char *_text)
            :m_text(_text),
              m_style(stretch),
              m_left(24),
              m_top(4),
              m_bottom(2),
              m_right(2),
              m_status(normal),
              m_toggle(false)
		{
            m_size=getPreferedSize();

            mouseEnteredHandlerList.push_back(MOUSE_DELEGATE(MenuItemToggleButton::mouseEntered));
            mouseExitedHandlerList.push_back(MOUSE_DELEGATE(MenuItemToggleButton::mouseExited));
            mousePressedHandlerList.push_back(MOUSE_DELEGATE(MenuItemToggleButton::mousePressed));
            mouseReleasedHandlerList.push_back(MOUSE_DELEGATE(MenuItemToggleButton::mouseReleased));
		}

		MenuItemToggleButton::~MenuItemToggleButton(void)
		{
		}

		void MenuItemToggleButton::mousePressed(const Event::MouseEvent &e)
		{
            m_status=pressed;
        }
		
		void MenuItemToggleButton::mouseEntered(const Event::MouseEvent &e)
		{
			isHover=true;
            m_status=hover;
        }

		void MenuItemToggleButton::mouseReleased(const Event::MouseEvent &e)
		{
            m_status=hover;
            m_toggle=!m_toggle;
        }

		void MenuItemToggleButton::mouseExited(const Event::MouseEvent &e)
		{
			isHover=false;
            m_status=normal;
        }
	}
}
