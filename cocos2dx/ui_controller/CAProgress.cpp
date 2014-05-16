//
//  CASlider.cpp
//  project
//
//  Created by lh on 14-4-16.
//  Copyright (c) 2014 www.9miao.com All rights reserved.
//

#include "CAProgress.h"
#include "actions/CCActionInterval.h"
#include "sprite_nodes/CCScale9Sprite.h"
#include "CCDirector.h"
#include "CCScheduler.h"
#include "support/CCPointExtension.h"
NS_CC_BEGIN

CAProgress::CAProgress()
:m_fProgress(0.0f)
,m_pProgressTintColor(ccBLUE)
,m_pProgresstrackColor(ccGRAY)
,m_pProgressStyle(CAProgressStyleDefault)
,m_pProgressTintImage("")
,m_pProgressTrackImage("")
,m_nCurPercent(0.0f)
,m_pCopyProgressImage(NULL)
,m_pCopyTarckImage(NULL)
,m_previousPercent(0.0f)
{
    m_pIndicator=CAView::create();
    m_pIndicator->retain();
}

CAProgress::~CAProgress()
{
    CC_SAFE_DELETE(m_pIndicator);
    
}

CAProgress* CAProgress::create()
{
    CAProgress *progress = new CAProgress();
    if (progress && progress->init())
    {
        progress->autorelease();
        return progress;
    }
    CC_SAFE_DELETE(progress);
    return NULL;
}

void CAProgress::setProgress(float progress, bool animated)
{

    progress = MIN(1.0f, progress);
    progress = MAX(0.0f, progress);
    m_previousPercent=m_nCurPercent;
    m_nCurPercent=progress;
    if (animated)
    {
        CCDirector::sharedDirector()->getScheduler()->scheduleSelector(schedule_selector(CAProgress::schedule), this, 1/60.0f, false);
        
        CCMoveTo *pMoveTo=CCMoveTo::create((progress/1.0f)*0.3, ccp(this->getFrame().size.width*progress, 0));
        
        m_pIndicator->runAction(pMoveTo);
    }
    else
    {
        if (m_pCopyProgressImage)
        {
            m_pCopyProgressImage->setTextureRect(CCRectMake(m_pCopyProgressImage->getPosition().x, m_pCopyProgressImage->getPosition().y, m_pCopyProgressImage->getFrame().size.width*progress, m_pCopyProgressImage->getFrame().size.height));
        }
        else
        {
            m_fProgress=progress;
        }
    }
    
    
}

bool CAProgress::init()
{
    if (!CAView::init())
    {
        return false;
    }
    CCSize winSize=CCDirector::sharedDirector()->getWinSize();
    m_pRender=CCRenderTexture::create(winSize.width, winSize.height, kCCTexture2DPixelFormat_RGBA8888);
    m_pRender->setPosition(ccp(winSize.width/2, winSize.height/2));

    
    return true;

}
void CAProgress::onEnterTransitionDidFinish()
{
    
    CAView::onEnterTransitionDidFinish();
    
  
    if (m_pCopyTarckImage == NULL ) 
	{
        this->init9SpriteWithImage("biggraycircle2.png");
        
        m_pCopyTarckImage=CCSprite::createWithTexture(m_pRender->getSprite()->getTexture());
        m_pCopyTarckImage->setPosition(CCPointZero);
        m_pCopyTarckImage->setAnchorPoint(CCPointZero);
        this->addSubview(m_pCopyTarckImage);
        
        
        
        this->init9SpriteWithImage("dabluecircle.png");
        
        m_pCopyProgressImage=CCSprite::createWithTexture(m_pRender->getSprite()->getTexture());
        m_pCopyProgressImage->setAnchorPoint(CCPointZero);
        m_pCopyProgressImage->setPosition(CCPointZero);
        m_pCopyProgressImage->setTextureRect(CCRectMake(m_pCopyProgressImage->getPosition().x, m_pCopyProgressImage->getPosition().y, m_pCopyProgressImage->getFrame().size.width*m_fProgress, m_pCopyProgressImage->getFrame().size.height));
        this->addSubview(m_pCopyProgressImage);
        m_pIndicator->setFrame(CCRectMake(m_pCopyProgressImage->getPosition().x, m_pCopyProgressImage->getPosition().y, 0, 0));
        this->addSubview(m_pIndicator);
    }
}

void CAProgress::init9SpriteWithImage(const char *fileName)
{
    CCScale9Sprite *tarckImage=CCScale9Sprite::createWithTexture(CCTexture2D::create(fileName));
    CCRect tarckTap;
    tarckTap.origin=tarckImage->getFrame().size/2;
    tarckTap.origin=ccpSub(tarckTap.origin, CCPoint(1, 1));
    tarckTap.size=CCSize(2, 2);
    tarckImage->setCapInsets(tarckTap);
    tarckImage->setPreferredSize(m_obContentSize);
    tarckImage->setAnchorPoint(CCPointZero);
    this->addSubview(tarckImage);
    
    
    
    m_pRender->initWithWidthAndHeight(tarckImage->getFrame().size.width, tarckImage->getFrame().size.height, kCCTexture2DPixelFormat_RGBA8888);
    m_pRender->setPosition(tarckImage->getPosition());
    m_pRender->begin();
    tarckImage->visit();
    m_pRender->end();
    this->removeSubview(tarckImage);
}

void CAProgress::setProgressTintImage(std::string var)
{
    m_pProgressTintImage=var;
    this->init9SpriteWithImage(var.c_str());
    m_pCopyProgressImage->initWithTexture(m_pRender->getSprite()->getTexture());
}

std::string CAProgress::getProgressTintImage()
{
    return m_pProgressTintImage;
}

void CAProgress::setProgressTrackImage(std::string var)
{
    m_pProgressTrackImage=var;
    this->init9SpriteWithImage(var.c_str());
    m_pCopyTarckImage->initWithTexture(m_pRender->getSprite()->getTexture());
    
}

std::string CAProgress::getProgressTrackImage()
{
    return m_pProgressTrackImage;
}

void CAProgress::onExitTransitionDidStart()
{
    CAView::onExitTransitionDidStart();
}

void CAProgress::schedule(float dt)
{
    if(m_pCopyProgressImage->getFrame().size.width<m_pCopyTarckImage->getFrame().size.width*m_nCurPercent)
    {

        m_pCopyProgressImage->setTextureRect(CCRectMake(m_pCopyProgressImage->getPosition().x, m_pCopyProgressImage->getPosition().y, m_pIndicator->getPosition().x, m_pCopyProgressImage->getFrame().size.height));
        
    }
    else
    {
        CCDirector::sharedDirector()->getScheduler()->unscheduleSelector(schedule_selector(CAProgress::schedule), this);
    }
    
    
}

NS_CC_END
