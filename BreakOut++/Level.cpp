#include "Level.h"

Level::Level(int level, PlaySideBar* sideBar,Player* player,Ball* ball) {
	
	mTimer = Timer::Instance();
	mSideBar = sideBar;
	mSideBar->SetLevel(level);

	mLevel = level;
	mLevelStarted = false;

	mLabelTimer = 0.0f;

	mLevelLabel = new Texture("Level", "emulogic.ttf", 24, { 75,75,200 });
	mLevelLabel->Parent(this);
	mLevelLabel->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.6f, Graphics::Instance()->SCREEN_HEIGHT * 0.5f));

	mLevelNumber = new ScoreBoard({ 75,75,200 });
	mLevelNumber->Score(mLevel);
	mLevelNumber->Parent(this);
	mLevelNumber->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.7f, Graphics::Instance()->SCREEN_HEIGHT * 0.5f));

	mLevelLabelOnScreen = 0.0f;
	mLevelLabelOffScreen = 1.5f;

	mReadyLabel = new Texture("READY", "emulogic.ttf", 24, { 75,75,200 });
	mReadyLabel->Parent(this);
	mReadyLabel->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.62f, Graphics::Instance()->SCREEN_HEIGHT * 0.5f));

	mReadyLabelOnScreen = mLevelLabelOffScreen;
	mReadyLabelOffScreen = mReadyLabelOnScreen + 3.0f;

	mBall = ball;

	mPlayer = player;
	mBallDropped = false;
	mPlayerRespawnDelay=3.0f;
	mPlayerRespawnTimer = 0.0f;
	mPlayerRespawnLabelOnScreen = 2.0f;

	mGameOverLabel = new Texture("GAME OVER", "emulogic.ttf", 32, { 150,0,0 });
	mGameOverLabel->Parent(this);
	mGameOverLabel->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.62f, Graphics::Instance()->SCREEN_HEIGHT * 0.5f));

	mGameOver = false;
	mGameOverDelay = 4.0f;
	mGameOverTimer = 0.0f;
	mGameOverLabelOnScreen = 1.0f;

	ParseXml();
	Brick::CurrentPlayer(mPlayer);


	mCurrentState = running;
}

Level::~Level() {
	mTimer = NULL;
	mSideBar = NULL;

	delete mLevelLabel;
	mLevelLabel = NULL;
	delete mLevelNumber;
	mLevelNumber = NULL;

	delete mReadyLabel;
	mReadyLabel = NULL;

	mPlayer = NULL;
	mBall = NULL;

	delete mGameOverLabel;
	mGameOverLabel = NULL;

	for (auto brick : mBricks) {
		delete brick;
		brick = NULL;
	}
	mBricks.clear();

	for (auto brick : mBrickTypes) {
		delete brick;
		brick = NULL;
	}
	mBrickTypes.clear();

}

void Level::StartLevel() {
	mLevelStarted = true;
}

void Level::HandleStartLabels() {
	mLabelTimer += mTimer->DeltaTime();
	if (mLabelTimer >= mLevelLabelOffScreen) {
		if (mLevel > 1) {
			StartLevel();
		}
		else {
			if (mLabelTimer >= mReadyLabelOffScreen) {

				StartLevel();
				mPlayer->Active(true);
				mPlayer->Visible(true);

				mBall->Active(true);
				mBall->Visible(true);
			}
		}
	}
}



void Level::HandleCollisions() {
	if (!mBallDropped) {
		if (mBall->Speed()==0) {
			mPlayer->DroppedBall();
			mSideBar->SetLifes(mPlayer->Lives());

			mBallDropped = true;
			mPlayerRespawnTimer = 0.0f;
			mPlayer->Active(false);
			mBall->Active(false);
		}
	}
}

void Level::ResetBall() {
	mBall->Parent(mPlayer);
	mBall->Docked(true);
	mBall->Pos(Vector2(0.0f, -25.0f));
	mBall->Direction(Vector2(0.0f, -1.0f));
	mBall->ResetSpeed();
	mBall->Active(false);
}

void Level::HandlePlayerDeath() {

	if (!mPlayer->IsAnimating()) {

		if (mPlayer->Lives() > 0) {
			
			if (mPlayerRespawnTimer == 0.0f) {
				mPlayer->Visible(false);
				mBall->Visible(false);
			}
			mPlayerRespawnTimer += mTimer->DeltaTime();

			if (mPlayerRespawnTimer >= mPlayerRespawnDelay) {
				mPlayer->Active(true);
				mPlayer->Visible(true);

				ResetBall();
				mBall->Active(true);
				mBall->Visible(true);

				mBallDropped = false;


			}
		}
		else {
			if (mGameOver == 0.0f)
				mPlayer->Visible(false);

			mGameOverTimer += mTimer->DeltaTime();
			if (mGameOverTimer >= mGameOverDelay) {
				mCurrentState = gameover;
			}
		}

	}
}

Level::LEVEL_STATES Level::State() {
	return mCurrentState;
}
void Level::ParseXml() {
	mBrickTypes.clear();
	mBricks.clear();
	XMLDocument doc(true,COLLAPSE_WHITESPACE);
	std::string fullpath = SDL_GetBasePath();
	fullpath.append("Assets/Level/level_" + std::to_string(mLevel) + ".xml");
	doc.LoadFile(fullpath.c_str());
	const XMLDocument& cdoc = doc;
	
	mRowCount = atoi(cdoc.FirstChildElement("Level")->FindAttribute("RowCount")->Value());
	mColumnCount = atoi(cdoc.FirstChildElement("Level")->FindAttribute("ColumnCount")->Value());
	mRowSpacing = atoi(cdoc.FirstChildElement("Level")->FindAttribute("RowSpacing")->Value());
	mColumnSpacing = atoi(cdoc.FirstChildElement("Level")->FindAttribute("ColumnSpacing")->Value());
	mColumnSpacing =atoi(cdoc.FirstChildElement("Level")->FindAttribute("ColumnSpacing")->Value());
	mBackgroundTexture = cdoc.FirstChildElement("Level")->FindAttribute("BackgroundTexture")->Value();

	tinyxml2::XMLElement* brickElement = doc.FirstChildElement("Level")->FirstChildElement("BrickTypes");
	for (tinyxml2::XMLElement* child = brickElement->FirstChildElement(); child != NULL; child = child->NextSiblingElement())
	{
		std::string tmpId = child->FindAttribute("Id")->Value();
		int tmpBreakScore = atoi(child->FindAttribute("BreakScore")->Value());
		int tmpHitPoints = atoi(child->FindAttribute("HitPoints")->Value());
		std::string tmpHitSound = child->FindAttribute("HitSound")->Value();
		std::string tmpBreakSound = child->FindAttribute("BreakSound")->Value();
		std::string tmpTexture = child->FindAttribute("Texture")->Value();
		mBrickTypes.push_back(new Brick(tmpId[0], tmpHitSound, tmpBreakSound, tmpTexture, tmpHitPoints, tmpBreakScore));
	}


	std::string tmp=cdoc.FirstChildElement("Level")->FirstChildElement("Bricks")->GetText();
	std::cout << tmp << std::endl;
	mBrickContainer = new GameEntity();
	mBrickContainer->Parent(this);
	mBrickContainer->Pos(Vector2(545.0f-(mColumnCount*50.0f+mColumnCount*mColumnSpacing)/2.0f,Graphics::Instance()->SCREEN_HEIGHT*0.1f));
	int k = 0, h = 0, total = 0;
	for (int i = 0; i < (mRowCount*mColumnCount)*2; i+=2) {
		
		for (int j = 0; j < mBrickTypes.size(); j++) {
			if (tmp[i] == '-') {
				k++;
				break;
			}
			else if (mBrickTypes[j]->BrickId() == tmp[i]) {
				mBricks.push_back(mBrickTypes[j]->Clone());
				mBricks[total]->Parent(mBrickContainer);
				if (k > mColumnCount-1) {
					h++;
					k = 0;
				}
				mBricks[total]->Pos(Vector2((50.0f + (float)mColumnSpacing) * k, (25.0f + (float)mColumnSpacing) * h ));
				k++;
				total++;
			}
		}
	}
}
void Level::GetBricksOnScreen() {
	
	for (auto brick : mBricks) {
		brick->Render();
	}
	
}

void Level::Update() {
	if (!mLevelStarted) {
		HandleStartLabels();
	}
	else {
		HandleCollisions();

		if (mBallDropped) {

			HandlePlayerDeath();

		} else{
			bool q = true;
			for (auto brick : mBricks) {
				brick->Update();
				if (brick->BrickId() != 'I') {
					q = q & !brick->Visible();
				}
			}
			if (q) {
				mCurrentState = finished;
			}

			if (InputManager::Instance()->KeyPressed(SDL_SCANCODE_SPACE)) {
				mBall->Parent(this);
				mBall->Docked(false);
			}
		}
	}
}


void Level::Render() {
	if (!mLevelStarted) {
		if (mLabelTimer > mLevelLabelOnScreen && mLabelTimer < mLevelLabelOffScreen) {
			mLevelLabel->Render();
			mLevelNumber->Render();
		} else if (mLabelTimer > mReadyLabelOnScreen && mLabelTimer < mReadyLabelOffScreen) {

			mReadyLabel->Render();
		
		}
	}
	else
	{
		GetBricksOnScreen();
		if (mBallDropped) {
			if (mPlayerRespawnTimer >= mPlayerRespawnLabelOnScreen)
				mReadyLabel->Render();

			if (mGameOverTimer >= mGameOverLabelOnScreen)
				mGameOverLabel->Render();
		}
	}
}
