import pytest


async def test_shorten_basic(service_client):
    url = 'https://google.com'
    response = await service_client.post('/v1/shorten', params={'url': url})

    assert response.status == 200
    assert 'id=' in response.text


async def test_blacklist(service_client):
    bad_url = 'http://malware.ru/danger'
    response = await service_client.post(
        '/v1/shorten',
        params={'url': bad_url})

    assert response.status == 403
    assert 'blacklisted' in response.text
