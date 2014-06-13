#include "ParticleSystem.h"

void ParticleSystem::AddEffect(ParticleEffect* effect){
	particleEffects.push_back(effect);
}


void ParticleSystem::RemoveEffect(int index){
	vector<ParticleEffect*>::iterator removedEff = particleEffects.begin() + index;
	particleEffects.erase(removedEff);
	delete &removedEff;
}

void ParticleSystem::RemoveEffect(ParticleEffect* effect){
	bool found = false;

	unsigned int index = 0;
	vector<ParticleEffect*>::iterator iter = particleEffects.begin(); 
	while(iter != particleEffects.end() && !found && (index < particleEffects.size())){
		if (effect == *iter){
			iter = particleEffects.erase(iter);
			found = true;
		}
		else iter = particleEffects.begin() + index;

		index++;
	}
}

void ParticleSystem::Update(bool isThrusting, float angle, Vector2 pos, float dt){
	LOG(Info, "Updating particle system");
	vector<ParticleEffect*> deletedEffects;

	for(vector<ParticleEffect*>::iterator iter = particleEffects.begin(); iter != particleEffects.end(); iter++){
		ParticleEffect* nextEffect = *iter;
		UpdateColors(nextEffect->colorChange, nextEffect->particles, nextEffect->numOfParticles);
		bool isAlive = nextEffect->update(isThrusting, angle, pos, dt);

		if (!isAlive){
			deletedEffects.push_back(nextEffect);
		}
	}

	for(vector<ParticleEffect*>::iterator iter = deletedEffects.begin(); iter != deletedEffects.end(); iter++){
		ParticleEffect* nextEffect = *iter;
		RemoveEffect(nextEffect);
	}
}

void ParticleSystem::Draw(Core::Graphics& graphics){
	for(vector<ParticleEffect*>::iterator iter = particleEffects.begin(); iter != particleEffects.end(); iter++){
		ParticleEffect* nextEffect = *iter;
		nextEffect->draw(graphics);
	}
}

void ParticleSystem::UpdateColors(ColorChangeType type, Particle* particles, int numParticles){
	for (int i = 0; i < numParticles; i++){
		int redValue = 255;
		int greenValue = 255;
		int blueValue = 255;
		Particle* p = (particles + i);
		float ageRatio = p->age / p->lifetime;

		if (type == ColorChangeType::BUBBLE){
			float blueDecreaseRatio = 0.8f;

			float blueRatio = 1.0f;

			if (ageRatio > blueDecreaseRatio){
				blueRatio = (1.0f - ageRatio) / (1.0f - blueDecreaseRatio);
			}

			redValue = int((1.0f - ageRatio) * 200.0f);
			greenValue = int((1.0f - ageRatio) * 200.0f);
			blueValue = int(blueRatio * 255);



		}
		else if (type == ColorChangeType::FIRE){
			// white > yellow > orange > red > black

			// 255, 255, 255
			// 255, 255, 0
			// 255, 0, 0
			// 0, 0, 0

			if (ageRatio < 0.33f){
				float blueRatio = 1.0f - (ageRatio / 0.33f);
				blueValue = int(255 * blueRatio);
			}
			else if (ageRatio >= 0.33f && ageRatio < 0.67f){
				float greenRatio = 1.0f - ((ageRatio - 0.33f) / 0.34f);
				greenValue = int(255 * greenRatio);

				blueValue = 0;
			}
			else if (ageRatio < 1.0f){
				float redRatio = 1.0f - ((ageRatio - 0.67f) / 0.33f);
				redValue = int(255 * redRatio);

				blueValue = 0;
				greenValue = 0;
			}
		}
		else if (type == ColorChangeType::EXPLOSION){
			// NOT YET IMPLEMENTED
		}

		p->currentColor = RGB(redValue, greenValue, blueValue);
	}
}