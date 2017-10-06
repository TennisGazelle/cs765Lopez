import React from 'react'
import { render } from 'react-dom'
import { Provider } from 'react-redux'
import { ConnectedRouter } from 'react-router-redux'
import store, { history } from './store'
import App from './containers/app'
import avClient from './modules/clients/AlphaVantageClient';

import 'sanitize.css/sanitize.css'
import './index.css'

const target = document.querySelector('#root')

render(
  <Provider store={store}>
    <ConnectedRouter history={history}>
      <div>
        <App />
        <div>
          {avClient.getInformationAbout({symbol: 'AAPL'})}
        </div>
      </div>
    </ConnectedRouter>
  </Provider>,
  target
)
