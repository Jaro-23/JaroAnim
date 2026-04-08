#pragma once

#include <functional>
#include <vector>

namespace JaroViewer {
	template<typename Self, typename EventType>
	class EventSender {
	public:
		size_t addListener(std::function<void(Self*, EventType)> listener);
		void updateListener(size_t ident, std::function<void(Self*, EventType)> listener);
		void removeListener(size_t ident);

		void send(Self* self, EventType event) const;

	private:
		struct Listener {
			bool active;
			std::function<void(Self*, EventType)> callback;
		};

		std::vector<Listener> mListeners;
	};

	template<typename Self, typename EventType>
	size_t EventSender<Self, EventType>::addListener(std::function<void(Self*, EventType)> listener) {
		for (size_t i = 0; i < mListeners.size(); ++i) {
			if (mListeners.at(i).active) continue;
			mListeners.at(i).active   = true;
			mListeners.at(i).callback = listener;
			return i;
		}
		mListeners.push_back({true, listener});
		return mListeners.size() - 1;
	}

	template<typename Self, typename EventType>
	void EventSender<Self, EventType>::updateListener(size_t ident, std::function<void(Self*, EventType)> listener) {
		if (ident >= mListeners.size()) return;
		mListeners.at(ident).active   = true;
		mListeners.at(ident).callback = listener;
	}

	template<typename Self, typename EventType>
	void EventSender<Self, EventType>::removeListener(size_t ident) {
		if (ident >= mListeners.size()) return;
		mListeners.at(ident).active   = false;
		mListeners.at(ident).callback = [](Self*, EventType) {};
	}

	template<typename Self, typename EventType>
	void EventSender<Self, EventType>::send(Self* self, EventType event) const {
		for (auto& listener : mListeners)
			if (listener.active) listener.callback(self, event);
	}
} // namespace JaroViewer
