
#include "PageViewTest.h"

PageViewTest::PageViewTest():pageViewIndex(0)
{
    CADrawerController* drawer = (CADrawerController*)CAApplication::getApplication()->getRootWindow()->getRootViewController();
    drawer->setTouchMoved(false);
}

PageViewTest::~PageViewTest()
{
    CADrawerController* drawer = (CADrawerController*)CAApplication::getApplication()->getRootWindow()->getRootViewController();
    drawer->setTouchMoved(true);
}

void PageViewTest::viewDidLoad()
{
    CAImageView* view1 = CAImageView::createWithImage(CAImage::create("image/1.jpg"));
    CAImageView* view2 = CAImageView::createWithImage(CAImage::create("image/2.jpg"));
    CAImageView* view3 = CAImageView::createWithImage(CAImage::create("image/3.jpg"));
    CAVector<CAView*> _view;
    _view.pushBack(view1);
    _view.pushBack(view2);
    _view.pushBack(view3);
    
    p_pageView = CAPageView::createWithLayout(DLayoutFill, CAPageViewDirectionHorizontal);
        //DRectLayout(0,0,0,0, DRectLayout::L_R_T_B), CAPageViewDirectionHorizontal);//设置完图像不显示
    p_pageView->setViews(_view);
    p_pageView->setPageViewDelegate(this);
    this->getView()->addSubview(p_pageView);
    
    pageControl = CAPageControl::createWithLayout(DLayout(DHorizontalLayout_L_R(200, 200), DVerticalLayout_T_H(50, 50)));
                                                    //DRectLayout(200,200,50,50,DRectLayout::L_R_T_H));
    pageControl->setNumberOfPages((int)_view.size());
    pageControl->setPageIndicatorTintColor(CAColor_gray);
    pageControl->setCurrentPageIndicatorTintColor(CAColor_green);
    pageControl->addTarget(this, CAControl_selector(PageViewTest::pageControlCallBack));
    this->getView()->addSubview(pageControl);
}

void PageViewTest::viewDidUnload()
{
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}

void PageViewTest::pageViewDidBeginTurning(CAPageView* pageView)
{
    
}

void PageViewTest::pageViewDidEndTurning(CAPageView* pageView)
{
    if (pageViewIndex==0)
    {
        pageControl->setCurrentPage(pageView->getCurrPage());
        pageControl->updateCurrentPageDisplay();
    }
    else
    {
        
    }
}

void PageViewTest::pageControlCallBack(CrossApp::CAControl *btn, CrossApp::DPoint point)
{
    CAPageControl* button = (CAPageControl*)btn;
    CCLog("btn_tag===%d",button->getCurrentPage());
    p_pageView->setCurrPage(button->getCurrentPage(), true);
}

void PageViewTest::pageViewDidSelectPageAtIndex(CAPageView* pageView, unsigned int index, const DPoint& point)
{
    
}