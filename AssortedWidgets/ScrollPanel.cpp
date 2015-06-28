#include "ScrollPanel.h"
#include "ScrollBar.h"
#include "ThemeEngine.h"
#include "Graphics.h"
#include "MouseEvent.h"

namespace AssortedWidgets
{
	namespace Widgets
	{
		ScrollPanel::ScrollPanel(void):content(0),offsetX(0),offsetY(0),horizontalScrollStyle(Auto),verticalScrollStyle(Auto),offsetXMax(0),offsetYMax(0),horizontalBarShow(false),verticalBarShow(false)
		{
			horizontalBar=new ScrollBar(ScrollBar::Horizontal);
			verticalBar=new ScrollBar(ScrollBar::Vertical);
			setHorizontalStyle(Element::Stretch);
			setVerticalStyle(Element::Stretch);
			horizontalBar->setScrollPanel(this);
			verticalBar->setScrollPanel(this);

            mousePressedHandlerList.push_back(MOUSE_DELEGATE(ScrollPanel::mousePressed));
            mouseReleasedHandlerList.push_back(MOUSE_DELEGATE(ScrollPanel::mouseReleased));
            mouseEnteredHandlerList.push_back(MOUSE_DELEGATE(ScrollPanel::mouseEntered));
            mouseExitedHandlerList.push_back(MOUSE_DELEGATE(ScrollPanel::mouseExited));
            mouseMovedHandlerList.push_back(MOUSE_DELEGATE(ScrollPanel::mouseMoved));

			pack();
		}

		void ScrollPanel::mouseEntered(const Event::MouseEvent &e)
		{
			isHover=true;
            int mx=e.getX()-m_position.x;
            int my=e.getY()-m_position.y;
			if(verticalBar->isIn(mx,my))
			{
				Event::MouseEvent event(verticalBar,Event::MouseEvent::MOUSE_ENTERED,mx,my,0);
				verticalBar->processMouseEntered(event);
				return;
			}
			else if(horizontalBar->isIn(mx,my))
			{
				Event::MouseEvent event(horizontalBar,Event::MouseEvent::MOUSE_ENTERED,mx,my,0);
				horizontalBar->processMouseEntered(event);
				return;			
			}
		}

		void ScrollPanel::onValueChanged(ScrollBar *scrollBar)
		{
			if(scrollBar==horizontalBar)
			{
				offsetX=static_cast<unsigned int>(offsetXMax*scrollBar->getValue());
				if(content)
				{
                    content->m_position.x=-static_cast<int>(offsetX);
				}
			}
			else if(scrollBar==verticalBar)
			{
				offsetY=static_cast<unsigned int>(offsetYMax*scrollBar->getValue());
				if(content)
				{
                    content->m_position.y=-static_cast<int>(offsetY);
				}
			}
		}

		void ScrollPanel::mouseMoved(const Event::MouseEvent &e)
		{
            int mx=e.getX()-m_position.x;
            int my=e.getY()-m_position.y;
			if(verticalBar->isIn(mx,my))
			{
				if(verticalBar->isHover)
				{
					Event::MouseEvent event(verticalBar,Event::MouseEvent::MOUSE_MOTION,mx,my,0);
					verticalBar->processMouseMoved(event);
					return;
				}
				else
				{
					Event::MouseEvent event(verticalBar,Event::MouseEvent::MOUSE_ENTERED,mx,my,0);
					verticalBar->processMouseEntered(event);
					return;
				}
			}
			else
			{
				if(verticalBar->isHover)
				{
					Event::MouseEvent event(verticalBar,Event::MouseEvent::MOUSE_EXITED,mx,my,0);
					verticalBar->processMouseExited(event);
					return;				
				}
			}

			if(horizontalBar->isIn(mx,my))
			{
				if(horizontalBar->isHover)
				{
					Event::MouseEvent event(horizontalBar,Event::MouseEvent::MOUSE_MOTION,mx,my,0);
					horizontalBar->processMouseMoved(event);
					return;			
				}
				else
				{
					Event::MouseEvent event(horizontalBar,Event::MouseEvent::MOUSE_ENTERED,mx,my,0);
					horizontalBar->processMouseEntered(event);
					return;			
				}
			}	
			else
			{
				if(horizontalBar->isHover)
				{
					Event::MouseEvent event(horizontalBar,Event::MouseEvent::MOUSE_EXITED,mx,my,0);
					horizontalBar->processMouseExited(event);
					return;					
				}
			}
		}

		void ScrollPanel::mouseExited(const Event::MouseEvent &e)
		{
			isHover=false;
            int mx=e.getX()-m_position.x;
            int my=e.getY()-m_position.y;
			if(verticalBar->isHover)
			{
				Event::MouseEvent event(verticalBar,Event::MouseEvent::MOUSE_EXITED,mx,my,0);
				verticalBar->processMouseExited(event);
				return;
			}
			else if(horizontalBar->isHover)
			{
				Event::MouseEvent event(horizontalBar,Event::MouseEvent::MOUSE_EXITED,mx,my,0);
				horizontalBar->processMouseExited(event);
				return;			
			}	
		}

		void ScrollPanel::mouseReleased(const Event::MouseEvent &e)
		{
            int mx=e.getX()-m_position.x;
            int my=e.getY()-m_position.y;
			if(verticalBar->isIn(mx,my))
			{
				Event::MouseEvent event(verticalBar,Event::MouseEvent::MOUSE_RELEASED,mx,my,0);
				verticalBar->processMouseReleased(event);
				return;
			}
			else if(horizontalBar->isIn(mx,my))
			{
				Event::MouseEvent event(horizontalBar,Event::MouseEvent::MOUSE_RELEASED,mx,my,0);
				horizontalBar->processMouseReleased(event);
				return;			
			}
		}

		void ScrollPanel::mousePressed(const Event::MouseEvent &e)
		{
            int mx=e.getX()-m_position.x;
            int my=e.getY()-m_position.y;
			if(verticalBar->isIn(mx,my))
			{
				Event::MouseEvent event(verticalBar,Event::MouseEvent::MOUSE_PRESSED,mx,my,0);
				verticalBar->processMousePressed(event);
				return;
			}
			else if(horizontalBar->isIn(mx,my))
			{
				Event::MouseEvent event(horizontalBar,Event::MouseEvent::MOUSE_PRESSED,mx,my,0);
				horizontalBar->processMousePressed(event);
				return;			
			}
		}

		void ScrollPanel::pack()
		{
            scissorWidth=m_size.width-2;
            scissorHeight=m_size.height-2;
			if(content)
			{
                if(content->m_size.width>m_size.width-17 && horizontalScrollStyle==Auto)
				{
					horizontalBarShow=true;
					scissorWidth-=18;
                    horizontalBar->m_position.x=2;
                    horizontalBar->m_position.y=m_size.height-16;
                    horizontalBar->m_size.width=m_size.width-18;
					horizontalBar->pack();
				}
				else
				{
					horizontalBar->setValue(0);
					horizontalBarShow=false;
				}

                if(content->m_size.height>m_size.height-17 && verticalScrollStyle==Auto)
				{
					verticalBarShow=true;
					scissorHeight-=18;
                    verticalBar->m_position.x=m_size.width-16;
                    verticalBar->m_position.y=2;
                    verticalBar->m_size.height=m_size.height-18;
					verticalBar->pack();
				}
				else
				{
					verticalBar->setValue(0);
					verticalBarShow=false;
				}

                offsetXMax=std::max<unsigned int>(content->m_size.width-(m_size.width-17),0);
                offsetYMax=std::max<unsigned int>(content->m_size.height-(m_size.height-17),0);
				offsetX=static_cast<unsigned int>(offsetXMax*horizontalBar->getValue());
                content->m_position.x=-static_cast<int>(offsetX);
				offsetY=static_cast<int>(offsetYMax*verticalBar->getValue());
                content->m_position.y=-static_cast<int>(offsetY);
			}
		}

		void ScrollPanel::paint()
		{
			Theme::ThemeEngine::getSingleton().getTheme().paintScrollPanel(this);
            Util::Position p(m_position);
            Util::Graphics::getSingleton().pushPosition(p);

			if(horizontalBarShow)
			{
				horizontalBar->paint();
			}
			if(verticalBarShow)
			{
				verticalBar->paint();
			}
			Util::Position sPosition(2,2);
			Util::Size sArea(scissorWidth,scissorHeight);
			Theme::ThemeEngine::getSingleton().getTheme().scissorBegin(sPosition,sArea);
			if(content)
			{
				content->paint();
			}
			Theme::ThemeEngine::getSingleton().getTheme().scissorEnd();
			Util::Graphics::getSingleton().popPosition();
		}

		ScrollPanel::~ScrollPanel(void)
		{
			delete horizontalBar;
			delete verticalBar;
		}
	}
}
