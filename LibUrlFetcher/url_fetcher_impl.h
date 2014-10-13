#pragma once
#include "url_fetcher.h"
#include "url_request.h"
#include "http_request_headers.h"
#include "http_request_job.h"

namespace net
{
	class URLFetcherImpl : public URLFetcher
	{
	public:
		URLFetcherImpl(const std::string& url,
			RequestType request_type,
			URLFetcherDelegate* d);
		virtual ~URLFetcherImpl();

		virtual void SetReferrer(const std::string& referrer) override;

		virtual void SetExtraRequestHeaders(
			const std::string& extra_request_headers) override;

		virtual void AddExtraRequestHeader(const std::string& header_line) override;

		virtual void SetStopOnRedirect(bool stop_on_redirect) override;

		virtual void Start() override;

		virtual const std::string& GetOriginalURL() const override;

		virtual const std::string& GetURL() const override;

		virtual const URLRequestStatus& GetStatus() const override;

		virtual int GetResponseCode() const override;

		virtual void ReceivedContentWasMalformed() override;

		virtual bool GetResponseAsString(std::string* out_response_string) const override;

	private:
		std::string original_url_;                // The URL we were asked to fetch
		std::string url_;                         // The URL we eventually wound up at
		URLFetcher::RequestType request_type_;  // What type of request is this?
		URLRequestStatus status_;          // Status of the request
		URLFetcherDelegate* delegate_;     // Object to notify on completion
		UrlRequest* request_;
		int response_code_;                // HTTP status code for the request

		bool was_cancelled_;
		// Number of bytes received so far.
		int64 current_response_bytes_;
		// Total expected bytes to receive (-1 if it cannot be determined).
		int64 total_response_bytes_;

		HttpRequestHeaders extra_request_headers_;
		std::string referrer_;             // HTTP Referer header value and policy

		bool stop_on_redirect_{ false };
	};
}