#include "AudioHandler.h"

AudioHandler::AudioHandler() {}

void AudioHandler::play() {
	if (!pl.empty()) {
		AudioHandler::play(pl);
	}
}
void AudioHandler::play(const bool& enable) {
	if (!pl.empty()) {
		AudioHandler::play(pl, enable);
	}
}

void AudioHandler::play(const std::string& path) {
		buffer.loadFromFile(path);
		sound.setBuffer(buffer);
		sound.play();
		while (sound.getStatus() > 0) {}
}

void AudioHandler::play(const std::vector<std::string>& path) {

	int items = path.size();

	for (int i(0); i < items; ++i) {
		buffer.loadFromFile(path[i]);
		sound.setBuffer(buffer);
		sound.play();
		while (sound.getStatus() > 0) {}
	}

}

void AudioHandler::play(const std::vector<std::string>& path, const bool& enable) {

	int items = path.size();

	for (int i(0); i < items; ++i) {
		buffer.loadFromFile(path[i]);
		sound.setBuffer(buffer);
		sound.play();

		while (sound.getStatus() > 0) {
			Keys space(K_SPACEBAR);
			if (space.state() == PRESSED && enable) {
				sound.stop();
				i = items;
			}
		}
	}
}

void AudioHandler::playAsync(const std::string& path) {
	buffer.loadFromFile(path);
	sound.setBuffer(buffer);
	sound.play();
}

void AudioHandler::delPlaylist() { pl.clear(); }
